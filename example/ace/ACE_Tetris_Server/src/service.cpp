#include "service.h"

#include <iostream>
#include <ace/OS.h>


Service::Service(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor)
    : ACE_Event_Handler(reactor), peer_(ACE_INVALID_HANDLE)
{
    if(-1 == acceptor.accept(peer_, &addr_)) {
        delete this;
        return;
    }

    char addr_string[256];
    addr_.addr_to_string(addr_string, 256);

    std::cout << std::endl;
    std::cout << "# CLIENT ENTER : " << addr_string << std::endl;

    this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

Service::~Service(void) {}

ACE_HANDLE Service::get_handle(void) const {
    return this->peer_.get_handle();
}

int Service::handle_input(ACE_HANDLE fd) {
    const int BUF = 1024;
    unsigned char in[BUF];

    ACE_Time_Value vt(0,0);
    ssize_t len = this->peer_.recv(in, BUF, &vt);

    if(len <= 0) return -1;

    ACE_Message_Block* mb = new ACE_Message_Block(len);
    ACE_OS::memcpy(mb->wr_ptr(), in, len);
    mb->wr_ptr(len);
    send_datas_.enqueue_tail(mb);

    this->reactor()->register_handler(this, ACE_Event_Handler::WRITE_MASK);

    return 0;
}

int Service::handle_output(ACE_HANDLE fd){
    ACE_Message_Block* mb(NULL);
    ACE_Time_Value rt(0,0);

    do {

        this->send_datas_.dequeue_head(mb, &rt);

        ssize_t len = this->peer_.send(mb->rd_ptr(), mb->length(), &rt);
        if(len < 0) {
            mb->release();
            return -1;
        }

        mb->rd_ptr(len);
        if(mb->length() > 0) {
            this->send_datas_.enqueue_head(mb);
            break;
        }

        mb->release();

    } while(false);

    if(this->send_datas_.is_empty()) {
        ACE_Reactor_Mask m = ACE_Event_Handler::WRITE_MASK | ACE_Event_Handler::DONT_CALL;
        this->reactor()->remove_handler(this, m);
    }

    return 0;
}

int Service::handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask) {

    char addr_string[256];
    addr_.addr_to_string(addr_string, 256);

    std::cout << std::endl;
    std::cout << "# CLIENT EXIT : " << addr_string << std::endl;

    ACE_Reactor_Mask m =ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    this->send_datas_.flush();
    this->peer_.close();

    delete this;

    return 0;
}

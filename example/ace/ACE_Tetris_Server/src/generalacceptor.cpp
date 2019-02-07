#include "generalacceptor.h"

#include <ace/INET_Addr.h>
#include <iostream>
#include "service.h"

GeneralAcceptor::GeneralAcceptor(const char* ipstr, ACE_Reactor* reactor)
    : ACE_Event_Handler(reactor)
{
    ACE_INET_Addr addr(ipstr);

    int bret = acceptor_.open(addr, 1);
    if(-1 == bret) {
        std::cout << std::endl;
        std::cout << "Listen fail : " << ipstr << std::endl;
        delete this;
        return;
    }

    std::cout << std::endl;
    std::cout << "# SERVER START : " << ipstr << std::endl;

    this->reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

GeneralAcceptor::~GeneralAcceptor(void) {}

ACE_HANDLE GeneralAcceptor::get_handle(void) const {
    return this->acceptor_.get_handle();
}

int GeneralAcceptor::handle_input(ACE_HANDLE fd) {
    new Service(this->acceptor_, this->reactor());
    return 0;
}

int GeneralAcceptor::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) {
    ACE_Reactor_Mask m =ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    this->acceptor_.close();
    delete this;
    return 0;
}

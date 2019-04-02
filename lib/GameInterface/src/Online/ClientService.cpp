//
// Created by kim on 19. 1. 10.
//

#include  <iostream>
#include  <ace/OS.h>

#include "SDL2/SDL.h"
#include "../Event.h"
#include  "ClientService.h"

#include "PacketQueue.h"

using namespace game_interface;

ClientService::ClientService(ACE_Reactor* reactor)
    :ACE_Event_Handler(reactor),peer_(ACE_INVALID_HANDLE),state_(C_INIT)
{
}


ClientService::~ClientService(void)
{
}

void
ClientService::state(CSTATE  state){
    this->state_ = state;
    if( C_SUCCESS!=this->state_) return;
    this->reactor()->register_handler( this, ACE_Event_Handler::READ_MASK);
}

ClientService::CSTATE
ClientService::state() const{
    return  this->state_;
}

ACE_SOCK_Stream&
ClientService::peer(){
    return  this->peer_;
}

ACE_HANDLE
ClientService::get_handle (void) const{
    return  this->peer_.get_handle();
}

int
ClientService::handle_input (ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    const  int BUF =1024;
    unsigned  char* in = new unsigned char[BUF];

    ACE_Time_Value rt(0,0);

    ssize_t len = this->peer_.recv(in,BUF-1,&rt);
    if( len<=0){// 서버  종료  또는  통신  에러
        return -1;
    }

    in[len]=NULL;

    Packet p{in,len};
    p.toPacket();

    PacketQueue::getInstance().pushEvent(p);

    return 0;
}

int
ClientService::handle_close (ACE_HANDLE  handle,ACE_Reactor_Mask  close_mask){
    std::cout<<"Disconntected"<<std::endl;
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler( this, m);

    this->peer_.close();
    this->peer_.set_handle(ACE_INVALID_HANDLE);
    this->state(C_INIT);
    this->send_datas_.flush();
    return 0;
}


int
ClientService::send(void* data, ssize_t  len){
    if(C_SUCCESS!= this->state_) return -1;

    ACE_Message_Block* mb = new  ACE_Message_Block(len);
    ACE_OS::memcpy( mb->wr_ptr(), data, len);
    mb->wr_ptr(len);
    this->send_datas_.enqueue_tail( mb );
    this->reactor()->register_handler( this, ACE_Event_Handler::WRITE_MASK);
    this->reactor()->register_handler( this, ACE_Event_Handler::READ_MASK);
    return 0;
}

int
ClientService::handle_output (ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    ACE_Message_Block* mb(NULL);
    ACE_Time_Value rt(0,0);

    do {
        this->send_datas_.dequeue_head(mb,&rt);

        ssize_t len = this->peer_.send( mb->rd_ptr(), mb->length(),&rt);
        if( len < 0){//통신  에러  발생
            mb->release();
            return handle_input(fd);
        }

        mb->rd_ptr(len);
        if( mb->length()>0){
            this->send_datas_.enqueue_head(mb);
            break;
        }

        mb->release();

    }while(false);

    if( this->send_datas_.is_empty()){
        ACE_Reactor_Mask m = ACE_Event_Handler::WRITE_MASK | ACE_Event_Handler::DONT_CALL;
        this->reactor()->remove_handler(this, m);
    }

    return 0;
}
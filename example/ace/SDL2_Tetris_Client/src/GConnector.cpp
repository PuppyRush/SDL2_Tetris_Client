//
// Created by kim on 19. 1. 10.
//

#include "GConnector.h"
#include  <ace/INET_Addr.h>
#include  <iostream>

GConnector::GConnector(const  char* ipstr,ACE_Reactor* reactor, EchoService& stream)
        :ACE_Event_Handler(reactor),stream_(stream)
{
    ACE_INET_Addr addr(ipstr);
    ACE_Time_Value rt(0,0);

    connector_.connect( stream_.peer(),addr,&rt);
    stream_.state( EchoService::C_CONNECTING);

    this->reactor()->register_handler(this,ACE_Event_Handler::CONNECT_MASK);

}


GConnector::~GConnector(void)
{
}


ACE_HANDLE
GConnector::get_handle (void) const{
    return stream_.peer().get_handle();
}

int
GConnector::handle_input(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    //접속  실패
    std::cout<<std::endl<<"Connect fail"<<std::endl;
    stream_.state( EchoService::C_FAIL);
    return -1;
}

int
GConnector::handle_output(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    //접속  성공
    std::cout<<std::endl<<"Connect success"<<std::endl;
    this->connector_.complete(stream_.peer());
    stream_.state( EchoService::C_SUCCESS);

    return -1;
}

int
GConnector::handle_exception(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    // 접속  실패
    return handle_input(fd);
}

int
GConnector::handle_close (ACE_HANDLE  handle,ACE_Reactor_Mask  close_mask){
    ACE_Reactor_Mask m =ACE_Event_Handler::ALL_EVENTS_MASK|ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    delete  this;
    return 0;
}


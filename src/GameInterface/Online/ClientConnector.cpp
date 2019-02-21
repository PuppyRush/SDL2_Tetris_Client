//
// Created by kim on 19. 1. 10.
//

#include "ClientConnector.h"
#include  "ClientConnector.h"
#include  <ace/INET_Addr.h>
#include  <iostream>

using namespace game_interface;

ClientConnector::ClientConnector(const  char* ipstr,ACE_Reactor* reactor, ClientService& stream)
        :ACE_Event_Handler(reactor),m_stream(stream)
{
    ACE_INET_Addr addr(ipstr);
    ACE_Time_Value rt(0,0);

    m_connector.connect( m_stream.peer(),addr,&rt);
    m_stream.state( ClientService::C_CONNECTING);

    this->reactor()->register_handler(this,ACE_Event_Handler::CONNECT_MASK);

}


ClientConnector::~ClientConnector(void)
{
}


ACE_HANDLE
ClientConnector::get_handle (void) const{
    return m_stream.peer().get_handle();
}

int
ClientConnector::handle_input(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    //접속  실패
    std::cout<<std::endl<<"Connect fail"<<std::endl;
    m_stream.state( ClientService::C_FAIL);
    return -1;
}

int
ClientConnector::handle_output(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    //접속  성공
    std::cout<<std::endl<<"Connect success"<<std::endl;
    this->m_connector.complete(m_stream.peer());
    m_stream.state( ClientService::C_SUCCESS);

    return -1;
}

int
ClientConnector::handle_exception(ACE_HANDLE  fd/* = ACE_INVALID_HANDLE*/){
    // 접속  실패
    return handle_input(fd);
}

int
ClientConnector::handle_close (ACE_HANDLE  handle,ACE_Reactor_Mask  close_mask){
    ACE_Reactor_Mask m =ACE_Event_Handler::ALL_EVENTS_MASK|ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    delete  this;
    return 0;
}

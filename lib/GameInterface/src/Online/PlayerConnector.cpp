//
// Created by kim on 19. 1. 10.
//

#include "GameInterface/include/PlayerConnector.h"
#include  "GameInterface/include/PlayerConnector.h"
#include  <ace/INET_Addr.h>
#include  <iostream>

using namespace game_interface;

PlayerConnector::PlayerConnector(const char* ipstr, ACE_Reactor* reactor, PlayerService* stream)
        : ACE_Event_Handler(reactor), m_service(stream), m_ipstring(ipstr)
{

}

PlayerConnector::~PlayerConnector(void)
{
}

void PlayerConnector::connect()
{
    ACE_INET_Addr addr("127.0.0.1:12345");
    ACE_Time_Value rt(0, 0);

    m_connector.connect(m_service->peer(), addr, &rt);
    m_service->state(PlayerService::C_CONNECTING);
    this->reactor()->register_handler(this, ACE_Event_Handler::CONNECT_MASK);

}

ACE_HANDLE
PlayerConnector::get_handle(void) const
{
    return m_service->peer().get_handle();
}

int
PlayerConnector::handle_input(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    //접속  실패
    std::cout << std::endl << "Connect fail" << std::endl;
    m_service->state(PlayerService::C_FAIL);
    return -1;
}

int
PlayerConnector::handle_output(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    //접속  성공
    std::cout << std::endl << "Connect success" << std::endl;
    this->m_connector.complete(m_service->peer());
    m_service->state(PlayerService::C_SUCCESS);

    return -1;
}

int
PlayerConnector::handle_exception(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    // 접속  실패
    return handle_input(fd);
}

int
PlayerConnector::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    //delete  this;
    return 0;
}

//
// Created by kim on 19. 1. 10.
//

#ifndef GAMEINTERFACE_PLAYERCONNECTOR_H
#define GAMEINTERFACE_PLAYERCONNECTOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <memory>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Connector.h>
#include <ace/Init_ACE.h>

#include  "PlayerService.h"
#include  "TStruct.h"

namespace game_interface {

class PlayerConnector : public ACE_Event_Handler
{

public:
    PlayerConnector(std::string ipstr, ACE_Reactor* reactor, PlayerService* stream);

    virtual ~PlayerConnector(void);

    void connect();

    inline const bool isConnection() const noexcept
    { return m_isConnection = ((m_service->state()==PlayerService::C_SUCCESS) ? 1 : 0); }

    virtual ACE_HANDLE get_handle(void) const;

    //접속  이벤트
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_exception(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

private:
    std::string m_ipstring;
    mutable int m_isConnection;
    ACE_SOCK_Connector m_connector;
    PlayerService* m_service;
};

}

#endif //SIMPLE_ECHOCLIENT_GCONNECTOR_H


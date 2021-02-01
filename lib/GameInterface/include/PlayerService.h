//
// Created by kim on 19. 1. 10.
//

#ifndef GAMEINTERFACE_PLAYERSERVICE_H
#define GAMEINTERFACE_PLAYERSERVICE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#pragma  once

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Acceptor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/INET_Addr.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>

#include "Packet.h"

namespace game_interface {

class PlayerService : public ACE_Event_Handler
{
public:
    enum CSTATE
    {
        C_INIT,
        C_CONNECTING,
        C_FAIL,
        C_SUCCESS
    };

    virtual ~PlayerService(void);

    inline ACE_SOCK_Acceptor& acceptor()
    { return m_acceptor; }

    void state(CSTATE state);

    inline CSTATE state() const
    { return this->m_state; }

    inline ACE_SOCK_Stream& peer()
    { return this->m_peer; }

    virtual ACE_HANDLE get_handle(void) const;

    void sendPacket(const packet::Packet& packet) const;

protected:
    ACE_SOCK_Stream m_peer;
    CSTATE m_state;
    ACE_INET_Addr m_addr;
    mutable ACE_Message_Queue<ACE_MT_SYNCH> m_sendDatas;
    mutable ACE_Reactor* m_reactor;

    explicit PlayerService(ACE_Reactor* reactor);

    PlayerService(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor);

    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

private:
    int send(void* data, ssize_t len) const;

    ACE_SOCK_Acceptor m_acceptor;
};
}

#endif //SIMPLE_ECHOCLIENT_ECHOSERVICE_H

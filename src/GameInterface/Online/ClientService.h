//
// Created by kim on 19. 1. 10.
//

#ifndef SDLTETRIS_TCLIENT_TCLIENTSERVICE_H
#define SDLTETRIS_TCLIENT_TCLIENTSERVICE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>
#pragma  once

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Acceptor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/INET_Addr.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>

namespace game_interface {

class ClientService : public ACE_Event_Handler {
public:
    enum CSTATE {
        C_INIT,
        C_CONNECTING,
        C_FAIL,
        C_SUCCESS
    };

private:
    ACE_SOCK_Stream peer_;
    CSTATE state_;
    ACE_Message_Queue<ACE_MT_SYNCH> send_datas_;

public:
    ClientService(ACE_Reactor *reactor);
    ~ClientService(void);

    void state(CSTATE state);
    CSTATE state() const;

    ACE_SOCK_Stream &peer();
    virtual ACE_HANDLE get_handle(void) const;
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    int send(void *data, ssize_t len);
    int recv(void *data, ssize_t &len);
};
}

#endif //SIMPLE_ECHOCLIENT_ECHOSERVICE_H

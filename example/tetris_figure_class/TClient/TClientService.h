//
// Created by kim on 19. 1. 10.
//

#ifndef WIN32


#ifndef SDLTETRIS_TCLIENT_TCLIENTSERVICE_H
#define SDLTETRIS_TCLIENT_TCLIENTSERVICE_H

#pragma  once

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>

#include "Common/TDefine.h"

SDL_TETRIS_BEGIN

class TClientService : public  ACE_Event_Handler
{
public:
    enum  CSTATE{
        C_INIT,
        C_CONNECTING,
        C_FAIL,
        C_SUCCESS
    };

    TClientService(ACE_Reactor* reactor);
    ~TClientService(void);
    void state(CSTATE state);

    CSTATE state() const;
    ACE_SOCK_Stream& peer();

    virtual  ACE_HANDLE get_handle (void) const;
    virtual  int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual  int handle_close (ACE_HANDLE handle,ACE_Reactor_Mask close_mask);
    virtual  int handle_output (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    int send(void* data, ssize_t len);

private:
    ACE_SOCK_Stream                 peer_;
    CSTATE                          state_;
    ACE_Message_Queue<ACE_MT_SYNCH> send_datas_;
};

SDL_TETRIS_END

#endif //SIMPLE_ECHOCLIENT_ECHOSERVICE_H

#endif

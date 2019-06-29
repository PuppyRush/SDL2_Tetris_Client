//
// Created by kim on 19. 1. 10.
//

#ifndef WIN32

#ifndef SDLTETRIS_TCLIENT_TCLIENTCONNECTOR_H
#define SDLTETRIS_TCLIENT_TCLIENTCONNECTOR_H

#include <memory>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Connector.h>

#include  "TClientService.h"
#include "Common/TDefine.h"

SDL_TETRIS_BEGIN

class TClientConnector : public ACE_Event_Handler
{

public:
    TClientConnector(const char *ipstr, ACE_Reactor *reactor, TClientService &stream);
    virtual ~TClientConnector(void);

    virtual ACE_HANDLE get_handle(void) const;
    //접속  이벤트
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_exception(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

private:

    ACE_SOCK_Connector m_connector;
    TClientService& m_stream;
};

SDL_TETRIS_END

#endif //SIMPLE_ECHOCLIENT_GCONNECTOR_H

#endif
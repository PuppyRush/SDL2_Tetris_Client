//
// Created by kim on 19. 1. 10.
//

#ifndef SIMPLE_ECHOCLIENT_GCONNECTOR_H
#define SIMPLE_ECHOCLIENT_GCONNECTOR_H

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Connector.h>
#include  "EchoService.h"

class  GConnector:public  ACE_Event_Handler
{
private:
    ACE_SOCK_Connector connector_;
    EchoService&    stream_;
public:
    GConnector(const  char* ipstr,ACE_Reactor* reactor, EchoService& stream);
    ~GConnector(void);

    virtual  ACE_HANDLE get_handle (void) const;
    //접속  이벤트
    virtual  int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual  int handle_output (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual  int handle_exception (ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual  int handle_close (ACE_HANDLE handle,ACE_Reactor_Mask close_mask);
};


#endif //SIMPLE_ECHOCLIENT_GCONNECTOR_H

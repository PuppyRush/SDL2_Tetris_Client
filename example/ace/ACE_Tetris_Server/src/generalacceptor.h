#ifndef GENERALACCEPTOR_H
#define GENERALACCEPTOR_H

#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>

class GeneralAcceptor
    : public  ACE_Event_Handler
{
public:
    GeneralAcceptor(const char* ipstr, ACE_Reactor* reactor);
    ~GeneralAcceptor(void);

    virtual ACE_HANDLE get_handle(void) const;
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

private:
    ACE_SOCK_Acceptor acceptor_;
};

#endif // GENERALACCEPTOR_H

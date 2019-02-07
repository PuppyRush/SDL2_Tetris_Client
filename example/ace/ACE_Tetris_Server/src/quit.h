#ifndef QUIT_H
#define QUIT_H

#include  <ace/Reactor.h>
#include  <ace/Event_Handler.h>

class Quit
    : public ACE_Event_Handler
{
public:
    Quit(ACE_Reactor* reactor);
    ~Quit(void);

    virtual int handle_signal (int signum, siginfo_t * = 0, ucontext_t * = 0);
    virtual int handle_exception (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
};

#endif // QUIT_H

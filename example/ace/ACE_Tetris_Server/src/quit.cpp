#include "quit.h"

#include <ace/OS.h>

#define SIGBREAK 0

Quit::Quit(ACE_Reactor* reactor)
    : ACE_Event_Handler(reactor)
{
    this->reactor()->register_handler(SIGBREAK, this);
}

Quit::~Quit(void){}

int Quit::handle_signal(int signum, siginfo_t *, ucontext_t *) {
    this->reactor()->notify(this);
    ACE_OS::sleep(2);
    return 0;
}

int Quit::handle_exception(ACE_HANDLE fd) {
    this->reactor()->end_reactor_event_loop();
    return -1;
}

int Quit::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) {
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK;
    ACE_Event_Handler::DONT_CALL;

    this->reactor()->remove_handler(this, m);
    delete this;
    return 0;
}

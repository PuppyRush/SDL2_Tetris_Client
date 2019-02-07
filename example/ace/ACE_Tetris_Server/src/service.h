#ifndef SERVICE_H
#define SERVICE_H

#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <ace/INET_Addr.h>

// Double Ended Queue
#include <ace/Message_Queue.h>
#include <ace/Synch.h>


class Service :public ACE_Event_Handler
{
public:
    Service(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor);
    ~Service(void);

    virtual ACE_HANDLE get_handle (void) const;
    virtual int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);
private:
    ACE_SOCK_Stream peer_;
    ACE_INET_Addr addr_;
    ACE_Message_Queue<ACE_MT_SYNCH> send_datas_;
};

#endif // SERVICE_H

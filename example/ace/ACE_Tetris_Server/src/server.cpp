#include <iostream>
#include <ace/OS.h>
#include "generalacceptor.h"
#include "quit.h"
#include <ace/TP_Reactor.h>
#include <ace/Reactor.h>
#include <ace/Init_ACE.h>
//#include <pthread.h>
#include <boost/thread.hpp>

void event_loop(ACE_Reactor* application) {
    application->run_reactor_event_loop();
}

const char* tp_react_msg ="Reactor Thread";

int main(int argc, char* argv[])
{
    std::cout << "I AM LEADER FOLOWERS PATTERN SERVER!" << std::endl;
    std::cout << "I AM INITIALIZED." << std::endl;

    ACE::init();

    ACE_TP_Reactor tp;
    ACE_Reactor reactor(&tp);

    new Quit(&reactor);
    new GeneralAcceptor("127.0.0.1:12345" , &reactor);

//    pthread_t th_react;
//    pthread_create(&reactor, NULL, event_loop, (void*) tp_react_msg);
//    pthread_join(&reactor, NULL);

    boost::thread tp_react (event_loop, &reactor);
    tp_react.join();

    exit(0);
}

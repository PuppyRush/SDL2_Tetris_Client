//
// Created by kim on 19. 1. 10.
//



#include <ace/ACE.h>
#include <ace/Select_Reactor.h>
#include <ace/Reactor.h>
#include "GConnector.h"
#include "EchoService.h"
#include <boost/thread.hpp>
#include <string>
#include <ace/OS.h>
#include <ace/Init_ACE.h>
#include <iostream>

void fn(ACE_Reactor* app){
    app->owner( ACE_OS::thr_self());
    app->run_reactor_event_loop();
}

int  main(int  argc, char* argv[])
{
    ACE::init();

    ACE_Select_Reactor sr;
    ACE_Reactor reactor(&sr);

    EchoService stream(&reactor);

    new  GConnector("127.0.0.1:12345",&reactor, stream);

    boost::thread t1(fn,&reactor);

    std::string end("EXIT");
    std::string cmd;

    do {
        std::getline( std::cin,cmd);
        if( end == cmd){
            reactor.end_reactor_event_loop();
            break;
        }

        stream.send( (void*)cmd.c_str(), strlen( cmd.c_str() ) );

    } while( true);

    t1.join();

    ACE::fini();
    return 0;
}

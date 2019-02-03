//
// Created by kim on 19. 1. 10.
//

#include  <thread>
#include  <string>
#include  <iostream>

#include  <ace/ACE.h>
#include  <ace/Select_Reactor.h>
#include  <ace/Reactor.h>
#include <ace/Init_ACE.h>
#include  <ace/OS.h>

#include  "TClientConnector.h"
#include  "TClientService.h"

void fn(ACE_Reactor* app){
    app->owner( ACE_OS::thr_self());
    app->run_reactor_event_loop();
}

int connectServer()
{

    ACE::init();

    ACE_Select_Reactor sr;
    ACE_Reactor reactor(&sr);

    EchoService stream(&reactor);

    new  GConnector("127.0.0.1:12345",&reactor, stream);

    std::thread t1(fn,&reactor);

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
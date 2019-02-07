//
// Created by kim on 19. 1. 10.
//

#include "TClientController.h"

SDL_TETRIS

void fn(ACE_Reactor* app){
    app->owner( ACE_OS::thr_self());
    app->run_reactor_event_loop();
}

TClientController::TClientController()
    :m_port(12345),
     m_ip({127,0,0,1}),
     m_connetor(nullptr),
     m_service(nullptr)
    // m_aceSelectReactor(make_shared<ACE_Select_Reactor>())
{
    /*ACE::init();

    m_reactor = make_shared<ACE_Reactor>(m_aceSelectReactor.get());
    m_service = make_shared<ClientService>(m_reactor.get());*/
}

TClientController::~TClientController()
{
    ACE::fini();
    m_reactor->end_reactor_event_loop();
}

void TClientController::connectServer()
{

    ACE::init();

    m_aceSelectReactor = make_shared<ACE_Select_Reactor>();
    m_reactor = make_shared<ACE_Reactor>(m_aceSelectReactor.get());
    m_service = make_shared<ClientService>(m_reactor.get());

    new  ClientConnector("127.0.0.1:12345",m_reactor.get(), *m_service.get());

    m_clientThread = std::thread(fn,m_reactor.get());

}

void TClientController::send(const packet_type packet) {
    m_service->send((void *) packet.first, packet.second);
}

const TClientController::packet_type TClientController::recv() {
    char buf[512];
    ssize_t len=0;
   // m_service->recv(buf,len);
    return make_pair(buf,len);
}

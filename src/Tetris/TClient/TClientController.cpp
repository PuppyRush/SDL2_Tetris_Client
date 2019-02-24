//
// Created by kim on 19. 1. 10.
//

#include "TClientController.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;

void fn(ACE_Reactor* app){
    app->owner( ACE_OS::thr_self());
    app->run_reactor_event_loop();
}

TClientController::TClientController()
     :m_ip({127,0,0,1},12345),
     m_connetor(nullptr),
     m_service(nullptr)
{
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

    m_clientThread = thread(fn,m_reactor.get());

}

void TClientController::send(Packet& packet)
{

    auto bytes = packet.toByte();
    m_service->send((void *) bytes.first, bytes.second);
}


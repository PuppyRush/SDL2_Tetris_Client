//
// Created by kim on 19. 1. 10.
//

#include <chrono>
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
     m_service(nullptr),
     m_endConnect(false)
{
}

TClientController::~TClientController()
{
    if(m_endConnect)
    {
        ACE::fini();
        m_reactor->end_reactor_event_loop();
    }
}

void TClientController::connectServer()
{

    ACE::init();

    m_aceSelectReactor = make_shared<ACE_Select_Reactor>();
    m_reactor = make_shared<ACE_Reactor>(m_aceSelectReactor.get());
    m_service = make_shared<ClientService>(m_reactor.get());

    new  ClientConnector("127.0.0.1:12345",m_reactor.get(), *m_service.get());
    m_clientThread = thread(fn,m_reactor.get());
    m_endConnect = true;

    std::this_thread::sleep_for (std::chrono::milliseconds(500));
}

void TClientController::send(Packet& packet)
{
    packet.setHeader().where = messageDirection::CLIENT;
    packet.setHeader().timestamp = std::time(nullptr);

    printf("clinet send : %d %d %ld\n", packet.getHeader().destId, toUType( packet.getHeader().message),
        packet.getHeader().timestamp);


    auto bytes = packet.toByte();
    m_service->send((void *) bytes.first, bytes.second);
}


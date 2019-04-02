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
     :m_ip({127,0,0,1},12345)
{
    ACE::init();

    m_aceSelectReactor = make_shared<ACE_Select_Reactor>();
    m_reactor = make_shared<ACE_Reactor>(m_aceSelectReactor.get());
    m_service = make_shared<ClientService>(m_reactor.get());
    m_connector = make_shared<ClientConnector>("127.0.0.1:12345",m_reactor.get(), *m_service.get());
}

TClientController::~TClientController()
{
    if(m_connector->isConnection())
    {
        ACE::fini();
        m_reactor->end_reactor_event_loop();
    }
}

const bool TClientController::connectServer()
{
    m_connector->connect();

    if(m_connector->isConnection())
    {
        m_clientThread = thread(fn,m_reactor.get());
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
    return m_connector->isConnection();
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


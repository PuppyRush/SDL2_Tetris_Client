//
// Created by kim on 19. 1. 10.
//

#include <chrono>
#include "TClientController.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;
using namespace game_interface::packet;

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
    m_service = make_shared<PlayerService>(m_reactor.get());
    m_connector = make_shared<PlayerConnector>("127.0.0.1:12345",m_reactor.get(), *m_service.get());
}

TClientController::~TClientController()
{
    if(m_connector->isConnection())
    {
        ACE::fini();
        m_reactor->end_reactor_event_loop();
    }
}

bool TClientController::connectServer()
{
    m_connector->connect();

    m_clientThread = thread(fn,m_reactor.get());
    std::this_thread::sleep_for (std::chrono::milliseconds(300));

    return m_connector->isConnection();
}

void TClientController::send(const Packet& packet) const
{
    packet.updateLocale();

    std::cout << packet;
    auto bytes = packet.toByte();
    m_service->send((void *) bytes.first, bytes.second);
}


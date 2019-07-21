//
// Created by kim on 19. 1. 10.
//

#include <chrono>
#include "ClientService.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;
using namespace game_interface::packet;

void fn(ACE_Reactor* app)
{
    app->owner(ACE_OS::thr_self());
    app->run_reactor_event_loop();
}

ClientService::ClientService(std::shared_ptr<ACE_Reactor> reactor)
        : PlayerService(reactor.get()),
          m_ip({127, 0, 0, 1}, 12345),
          m_reactor(reactor),
          m_connector(make_shared<PlayerConnector>("127.0.0.1:12345", reactor.get(), this))
{
}

ClientService::~ClientService()
{
    if (m_connector->isConnection()) {
        ACE::fini();
        m_reactor->end_reactor_event_loop();
    }
}

bool ClientService::connectServer()
{
    m_connector->connect();

    if(m_clientThread.joinable())
    {
        this->reactor()->end_reactor_event_loop();
        m_clientThread.join();
    }

    m_clientThread = thread(fn, m_reactor.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    return m_connector->isConnection();
}


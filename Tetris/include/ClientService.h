//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_CLIENT_TCLIENTSERVICE_H
#define TETRIS_CLIENT_TCLIENTSERVICE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <memory>

#include  <ace/ACE.h>
#include  <ace/Select_Reactor.h>
#include  <ace/Reactor.h>

#include  <ace/OS.h>

#include "THeader.h"
#include "GameInterface/include/PlayerService.h"
#include "GameInterface/include/Type.h"
#include "GameInterface/include/Packet.h"
#include "GameInterface/include/PlayerConnector.h"
#include "GameInterface/include/PlayerService.h"
#include "GameInterface/include/TStruct.h"

SDL_TETRIS_BEGIN

class ClientService : public game_interface::PlayerService
{
public:

    explicit ClientService(std::shared_ptr<ACE_Reactor> );

    virtual ~ClientService();

    bool connectServer();

    inline bool isConnection() const noexcept
    {
        return m_connector->isConnection();
    }

private:
    game_interface::TIPString m_ip;
    std::shared_ptr<ACE_Reactor> m_reactor;
    std::shared_ptr<game_interface::PlayerConnector> m_connector;
    std::thread m_clientThread;
};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_TCLIENTCONTROLLER_H

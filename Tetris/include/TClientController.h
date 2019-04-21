//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H
#define TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

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

#include "Common/THeader.h"
#include "GameInterface/include/Type.h"
#include "GameInterface/include/TStruct.h"
#include "GameInterface/src/Online/Packet.h"
#include "GameInterface/src/Online/ClientConnector.h"
#include "GameInterface/src/Online/ClientService.h"

SDL_TETRIS_BEGIN

class TClientController : private boost::serialization::singleton<TClientController>
{
public:

    friend class boost::serialization::singleton<TClientController>;

    TClientController();
    ~TClientController();
    bool connectServer();
    void send(game_interface::Packet& pcket);
    //const Packet recv();

    inline bool isConnection() const noexcept {
        return m_connector->isConnection();
    }

    static TClientController& getInstance() {
        return boost::serialization::singleton<TClientController>::get_mutable_instance();;
    }

private:
    game_interface::TIPString m_ip;
    std::shared_ptr<game_interface::ClientService> m_service;
    std::shared_ptr<ACE_Reactor> m_reactor;
    std::shared_ptr<game_interface::ClientConnector> m_connector;
    std::shared_ptr<ACE_Select_Reactor> m_aceSelectReactor;
    std::thread m_clientThread;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

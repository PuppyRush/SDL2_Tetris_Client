//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H
#define TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <thread>
#include <string>
#include <iostream>
#include <memory>

#include  <ace/ACE.h>
#include  <ace/Select_Reactor.h>
#include  <ace/Reactor.h>
#include <ace/Init_ACE.h>
#include  <ace/OS.h>

#include "Tetris/Common/THeader.h"
#include "GameInterface/Type.h"
#include "GameInterface/TStruct.h"
#include "GameInterface/Online/Packet.h"
#include  "GameInterface/Online/ClientConnector.h"
#include  "GameInterface/Online/ClientService.h"


SDL_TETRIS_BEGIN

class TClientController final
{
public:


    TClientController();
    ~TClientController();
    void connectServer();
    void send(game_interface::Packet& pcket);
    //const Packet recv();

    bool isEndConnect() const {
        return m_endConnect;
    }
    void setEndConnect(bool m_endConnect) {
        TClientController::m_endConnect = m_endConnect;
    }

private:
    game_interface::TIPString m_ip;
    game_interface::t_port m_port;
    std::shared_ptr<game_interface::ClientConnector> m_connetor;
    std::shared_ptr<game_interface::ClientService> m_service;
    std::shared_ptr<ACE_Reactor> m_reactor;
    std::shared_ptr<ACE_Select_Reactor> m_aceSelectReactor;
    std::thread m_clientThread;
    bool m_endConnect = false;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

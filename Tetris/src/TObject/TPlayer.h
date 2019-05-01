//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_FIGURE_CLASS_TPLAYER_H
#define TETRIS_FIGURE_CLASS_TPLAYER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <cassert>

#include "GameInterface/src/Online/Packet.h"
#include "GameInterface/include/Player.h"
#include "Tetris/include/TFigureController.h"
#include "../../include/TClientController.h"
#include "../TObject/TScore.h"

SDL_TETRIS_BEGIN

class TPlayer : public game_interface::Player
{
public:

    TPlayer();

    virtual ~TPlayer();

    inline const game_interface::TIPString& getIP() const noexcept
    { return m_ip; }

    inline const bool isReady() const noexcept
    { return m_isReady; }

    inline const int getOrder() const noexcept
    { return m_order; }

    inline const bool isSurvive() const noexcept
    { return m_isSurvive; }

    inline TClientController& getClientController() noexcept
    {
        return m_clientCtl;
    }

    inline tetris_module::TFigureController& getController() noexcept
    {
        return m_gameCtl;
    }

    inline void setOrder(const int idx) noexcept
    { m_order = idx; }

    inline void setReady(const bool rdy) noexcept
    { m_isReady = rdy; }

    void command(const sdleasygui::t_eventType event);

    void sendPacket(game_interface::Packet&);

    void initialize();

    void startGame();

    void endGame();

    const bool connectServer();

    virtual void updateObserver(const game_interface::Packet&) override;

    void sendBoardInfo(const game_interface::t_id gameRoomUnique);

    void recvBoardInfo(const game_interface::Packet& packet);

    void recvInfo(const game_interface::Packet&);

    void sendDummySignal();

    void requestWaitingRoomInitInfo();

    virtual Json::Value toJson() const override
    { return Player::toJson(); }

    virtual const std::string_view& getUniqueName() const override
    { return game_interface::NAME_PLAYER; }

    static auto& getInstance()
    {
        static auto inst = std::make_shared<TPlayer>();
        return inst;
    }

private:
    int m_order;
    bool m_isReady;
    bool m_isSurvive;
    game_interface::TIPString m_ip;
    TScore m_score;

    tetris_module::TFigureController m_gameCtl = tetris_module::TFigureController{};
    TClientController& m_clientCtl = TClientController::getInstance();
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

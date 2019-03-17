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
#include "GameInterface/src/Object/Player.h"
#include "../Common/TDefine.h"
#include "../TClient/TClientController.h"
#include "../TFiguers/TFigureController.h"
#include "../TObject/TScore.h"

SDL_TETRIS_BEGIN

class TPlayer : public game_interface::Player, public boost::serialization::singleton<TPlayer>
{
public:

    friend class boost::serialization::singleton<TPlayer>;


    TPlayer();
    virtual ~TPlayer();

    inline const bool isReady() const noexcept { return m_isReady; }
    inline const int getOrder() const noexcept { return m_order; }
    inline const bool isSurvive() const noexcept { return m_isSurvive; }

    inline const std::shared_ptr<TFigureController> getController() const noexcept {
        assert(m_gameCtl && m_gameCtl.get());
        return m_gameCtl;
    }

    inline void setOrder(const int idx) noexcept { m_order = idx; }
    inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

    void command(const sdleasygui::t_eventType event);
    void sendPacket(game_interface::Packet &);
    void startGame();
    void endGame();
    void connectServer();

    virtual void updateObserver(const game_interface::Packet&) override;

    void recvWaitingRoomInit(const game_interface::Packet&);
    void recvInfo(const game_interface::Packet&);
    void sendInitInfo();
    void sendDummySignal();

    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}

    static std::shared_ptr<TPlayer> getInstance() {

        static auto inst = std::shared_ptr<TPlayer>
            (&boost::serialization::singleton<TPlayer>::get_mutable_instance());
        return inst;
    }

private:
    int m_order;
    bool m_isReady;
    bool m_isSurvive;
    game_interface::TIPString m_ip;
    TScore m_score;

    std::shared_ptr<TFigureController> m_gameCtl;
    TClientController m_clientCtl;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

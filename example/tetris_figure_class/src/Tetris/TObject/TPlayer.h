//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_FIGURE_CLASS_TPLAYER_H
#define TETRIS_FIGURE_CLASS_TPLAYER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TDefine.h"
#include "Tetris/TFiguers/TFigureController.h"

#include "GameInterface/Object/Player.h"
#include "Tetris/TObject/TScore.h"

SDL_TETRIS_BEGIN

class TPlayer final : public Player
{
public:

    TPlayer();
    virtual ~TPlayer() {}

    inline const bool isReady() const noexcept { return m_isReady; }
    inline const int getOrder() const noexcept { return m_order; }
    inline const bool isSurvive() const noexcept { return m_isSurvive; }
    inline const std::shared_ptr<TFigureController> getController() const noexcept { return m_ctl; }

    inline void setOrder(const int idx) noexcept { m_order = idx; }
    inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

private:
    int m_order;
    bool m_isReady;
    bool m_isSurvive;
    TIPString m_ip;
    TScore m_score;

    std::shared_ptr<TFigureController> m_ctl;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

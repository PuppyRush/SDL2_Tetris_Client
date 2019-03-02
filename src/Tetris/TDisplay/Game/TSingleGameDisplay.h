//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H
#define TERIS_FIGURE_CLASS_TGAMELOCALDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "TGameDisplay.h"
#include "Tetris/TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TSingleGameDisplay final : public TGameDisplay{

public:

    TSingleGameDisplay();
    virtual ~TSingleGameDisplay(){}

private:
    virtual void onClickedStart() override final;
    virtual void onClickedSuspend() override final;

    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onClose() override final;
    virtual void onCreate() override final;
    virtual void registerEvent() override final;

    virtual void updateObserver(const game_interface::Packet& ) override final {}
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

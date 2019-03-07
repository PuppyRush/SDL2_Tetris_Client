//
// Created by chaed on 18. 11. 18.
//

#ifndef UICLASSEXAMPLE_MAINONLINEDISPLAY_H
#define UICLASSEXAMPLE_MAINONLINEDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMultiMainDisplay final : public TMainDisplay
{
public:

    TMultiMainDisplay();
    virtual ~TMultiMainDisplay() = default;


private:
    virtual void onClickedOption() override final;
    virtual void onClickedBack() override final;
    virtual void onClickedEnterServer() override final;
    virtual void registerEvent() override final;
    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onTimerEvent() override final;

    [[deprecated("dont call this function in TMultiMainDisplay")]]
    virtual void onClickedStartLocalGame() override final {}

    virtual void updateObserver(const game_interface::Packet& ) override final {}
};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H

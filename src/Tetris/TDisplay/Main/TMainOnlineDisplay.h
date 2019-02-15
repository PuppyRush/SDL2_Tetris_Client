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

class TMainOnlineDisplay final : public TMainDisplay
{
public:

    TMainOnlineDisplay();
    virtual ~TMainOnlineDisplay(){}


private:
    virtual void onClickedOption() final;
    virtual void onClickedEnterServer() final;
    virtual void registerEvent() override final;
    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void onTimer() override final;

    [[deprecated("dont call this function in TMainOnlineDisplay")]]
    virtual void onClickedStartLocalGame() override final {}
};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H

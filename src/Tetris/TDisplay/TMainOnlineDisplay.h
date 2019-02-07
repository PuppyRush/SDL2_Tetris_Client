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
    virtual void onClickedEnterServer() final;
    virtual void onClickedStartLocalGame() override final {}
    virtual void registerEvent() override final;
    virtual void onDraw() override final;
    virtual void onPreInitialize() override final;
    virtual void event(const SDL_Event *event) override final;
    virtual void timer() override final;

};

SDL_TETRIS_END

#endif //UICLASSEXAMPLE_MAINONLINEDISPLAY_H

//
// Created by chaed on 18. 12. 18.
//

#ifndef TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
#define TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "SDLEasyGUI/Windows/DisplayInterface.h"

SDL_TETRIS_BEGIN

class TOptionDisplay final: public DisplayInterface
{
public:

    TOptionDisplay();

private:

    virtual void registerEvent() override final;
    virtual void onPreInitialize() override final;
    virtual void event(const SDL_Event *event) override final;
    virtual void timer() override final;
    virtual void onDraw() override final;

};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H

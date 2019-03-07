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

class TOptionDisplay final: public sdleasygui::DisplayInterface
{
public:

    TOptionDisplay();
    virtual ~TOptionDisplay(){}

private:

    virtual void registerEvent() override final;
    virtual void onPreInitialize() override final;
    virtual void onDraw() override final;
    void onClickedBack();

    virtual void updateObserver(const game_interface::Packet& ) override final {}
};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TOPTIONDISPLAY_H
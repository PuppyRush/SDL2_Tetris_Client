//
// Created by chaed on 18. 12. 18.
//

#include "TMainDisplay.h"

SDL_TETRIS
using namespace sdleasygui;

TMainDisplay::TMainDisplay()
{
    m_display = game_interface::toUType(TDisplay::Main);
}


void TMainDisplay::onDraw()
{
    DisplayInterface::onDraw();
}

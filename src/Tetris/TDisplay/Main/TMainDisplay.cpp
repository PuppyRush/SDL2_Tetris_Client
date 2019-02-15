//
// Created by chaed on 18. 12. 18.
//

#include "TMainDisplay.h"

SDL_TETRIS

TMainDisplay::TMainDisplay()
    :DisplayInterface()
{
    m_display = toUType(TDisplay::Main);
}


void TMainDisplay::onDraw()
{
    DisplayInterface::onDraw();
}

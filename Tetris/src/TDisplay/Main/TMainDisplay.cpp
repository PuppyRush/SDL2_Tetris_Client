//
// Created by chaed on 18. 12. 18.
//

#include "TMainDisplay.h"

SDL_TETRIS
using namespace sdleasygui;

TMainDisplay::TMainDisplay(const sdleasygui::t_id displayId)
        : TDisplayInterface(displayId)
{
    m_display = game_interface::toUType(TDisplay::Main);
}

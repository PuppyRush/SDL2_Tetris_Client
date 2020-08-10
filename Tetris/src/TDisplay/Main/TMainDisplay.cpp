//
// Created by chaed on 18. 12. 18.
//

#include <Tetris/include/TProperty.h>
#include "TMainDisplay.h"

SDL_TETRIS
using namespace seg;

TMainDisplay::TMainDisplay()
{
    m_display = game_interface::toUType( tetris_module::TDisplay::Main);
}

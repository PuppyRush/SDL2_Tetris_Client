//
// Created by chaed on 18. 12. 18.
//

#include "TMainDisplay.h"

SDL_TETRIS

TMainDisplay::TMainDisplay(const std::vector<Menu>& menus)
    :TDisplayInterface(menus)
{}

TMainDisplay::TMainDisplay(std::vector<Menu>&& menus)
    :TDisplayInterface(menus)
{}


//
// Created by chaed on 19. 1. 13.
//

#include "TPlayer.h"

SDL_TETRIS

TPlayer::TPlayer()
    :m_ctl(make_shared<TFigureController>())
{}

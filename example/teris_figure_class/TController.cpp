//
// Created by chaed on 18. 12. 15.
//

#include "TController.h"

SDL_TETRIS_BEGIN

TControllerInterface::~TControllerInterface()
{
    SDL_DestroyRenderer(getRenderer());
    SDL_DestroyWindow(getWindow());
    SDL_Quit();
}

SDL_TETRIS_END
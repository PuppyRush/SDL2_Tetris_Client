//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_SDL_INITIATOR_H
#define TETRIS_FIGURE_CLASS_SDL_INITIATOR_H

#include <string>
#include <memory>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>


static void SDLEasyGUI_Init()
{
    if( TTF_Init() != 0 ){
        std::string s("TTF_Init error: " );
        s.append(SDL_GetError());
        throw std::runtime_error(s);
    }

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::string s("SDL_Init error: " );
        s.append(SDL_GetError());
        throw std::runtime_error(s);
    }
}


#endif //TETRIS_FIGURE_CLASS_SDL_INITIATOR_H

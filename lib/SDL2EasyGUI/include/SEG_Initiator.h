//
// Created by chaed on 19. 2. 8.
//

#ifndef SDL2EASYGUI_INITIATOR_H
#define SDL2EASYGUI_INITIATOR_H

#include <string>
#include <memory>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "GameInterface/include/Atomic.h"

#include "DisplayController.h"

#undef main

namespace seg {

static void Start()
{
    DisplayController::getInstance().run();
}

template <typename _Dp>
static void SetMaindisplay()
{
    
    DisplayController::getInstance().setMainDisplay(make_display<_Dp>());
}

static void SDLEasyGUI_Init()
{

    if (TTF_Init() != 0) {
        std::string s("TTF_Init error: ");
        s.append(SDL_GetError());
        throw std::runtime_error(s);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::string s("SDL_Init error: ");
        s.append(SDL_GetError());
        throw std::runtime_error(s);
    }
    SDL_RegisterEvents(SEG_DRAW_DISPLAY);

}

}

#endif //SDL2EASYGUI_SDL_INITIATOR_H

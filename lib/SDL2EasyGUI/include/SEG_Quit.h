//
// Created by chaed on 19. 2. 10.
//

#ifndef SDL2EASYGUI_QUIT_H
#define SDL2EASYGUI_QUIT_H

#include <SDL2/SDL.h>

#include "DisplayController.h"

namespace seg {

void SDLEasyGUI_Quit()
{
    DisplayController::getInstance().finish();
    SDL_Quit();
}

}

#endif //SDL2EASYGUI_SEG_QUIT_H

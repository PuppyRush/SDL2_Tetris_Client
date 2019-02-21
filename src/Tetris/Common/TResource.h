//
// Created by chaed on 19. 2. 5.
//

#ifndef TETRIS_FIGURE_CLASS_RESOURCE_H
#define TETRIS_FIGURE_CLASS_RESOURCE_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDLEasyGUI/SEG_Resource.h"
#include "../Common/TDefine.h"

SDL_TETRIS_BEGIN

//dont use resource id as 0x0000 (NULL)
enum class resource : t_res {

    RESOURCE_START = SEG_RESROUCE_END+1,

    MAIN_SINGLE_GAME_START_BUTTON,
    MAIN_MULTI_GAME_START_BUTTON,
    MAIN_OPTION_BUTTON,
    OPTION_BACK,
    MAIN_EXIT,
    GAME_START,
    GAME_SUSPEND,
    ENTERSERVER_ID,
    ENTERSERVER_OK,

    GAME_END
};


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_RESOURCE_H

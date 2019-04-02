//
// Created by chaed on 19. 2. 5.
//

#ifndef TETRIS_FIGURE_CLASS_RESOURCE_H
#define TETRIS_FIGURE_CLASS_RESOURCE_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDL2EasyGUI/src/SEG_Resource.h"
#include "../Common/TDefine.h"

SDL_TETRIS_BEGIN

//dont use resource id as 0x0000 (NULL)
enum class resource : sdleasygui::t_res {

    RESOURCE_START = sdleasygui::SEG_RESROUCE_END+1,

    MAIN_SINGLE_GAME_START_BUTTON,
    MAIN_MULTI_GAME_START_BUTTON,
    MAIN_OPTION_BUTTON,
    OPTION_SPEED,
    OPTION_SPEED_1,
    OPTION_SPEED_2,
    OPTION_SPEED_3,
    OPTION_SPEED_4,
    OPTION_SPEED_5,
    OPTION_SPEED_6,
    OPTION_SPEED_7,
    OPTION_SPEED_8,
    OPTION_MAP,
    OPTION_MAP_PYRAMID,
    OPTION_MAP_RAIN,
    OPTION_MAP_RANDOMLY,
    OPTION_GRAPHIC,
    OPTION_GRAPHIC_DRAWLINE,
    OPTION_BACK,
    MAIN_EXIT,
    GAME_START,
    GAME_SUSPEND,
    ENTERSERVER_ID,
    ENTERSERVER_OK,
    ENTERSERVER_BACK,
    WAITINGROOM_GAMEROOM_BEGIN,
    WAITINGROOM_GAMEROOM_END = WAITINGROOM_GAMEROOM_BEGIN+100,
    WAITINGROOM_USERBOX,
    WAITINGROOM_CHATBOX,
    WAITINGROOM_CHAREDIT,
    WAITINGROOM_DISCONNECT,
    WAITINGROOM_CREATE,
    WAITINGROOM_CREATE_GAMEROOMNAME,
    WAITINGROOM_CREATE_OK,
    WAITINGROOM_CREATE_CANCEL,
    GAME_END
};


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_RESOURCE_H

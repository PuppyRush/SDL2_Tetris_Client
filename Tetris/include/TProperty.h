//
// Created by chaed on 18. 11. 24.
//

#ifndef TETRIS_CLIENT_TPROPERTY_H
#define TETRIS_CLIENT_TPROPERTY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TDefine.h"
#include "GameInterface/include/Event.h"

SDL_TETRIS_BEGIN

enum TetrisEvent
{

    TETRIS_EVENT_START = game_interface::toUType(seg::SEG_Event::SEGEVENT_END) + 1,
    TETRIS_EVENT_FIGURETIMER
};

typedef struct UserEvent
{
    static seg::t_eventType SDLEASYGUI_EVENT;
} UserEvent;

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

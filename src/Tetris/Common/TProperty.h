//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_TPROPERTY_H
#define TERIS_FIGURE_CLASS_TPROPERTY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TDefine.h"
#include "../../GameInterface/Event.h"

SDL_TETRIS_BEGIN

const sdleasygui::t_size UNIT_LENGTH = 30;
const sdleasygui::t_size GAMEBOARD_WIDTH_COUNT = 10;
const sdleasygui::t_size GAMEBOARD_HEIGHT_COUNT = 20;
const sdleasygui::t_size GAMEBOARD_DISPLAY_HEIGHT = UNIT_LENGTH*GAMEBOARD_HEIGHT_COUNT;
const sdleasygui::t_size GAMEBOARD_DISPLAY_WIDTH = UNIT_LENGTH*GAMEBOARD_WIDTH_COUNT;
const sdleasygui::t_size NEXTFIGURE_BOARD_WIDTH_COUNT = 3;
const sdleasygui::t_size NEXTFIGURE_BOARD_HEIGHT_COUNT = 4;
const sdleasygui::t_size GAMEBOARD_BEGIN_X = 20;
const sdleasygui::t_size GAMEBOARD_BEGIN_Y = 20;
const sdleasygui::t_size FIGURE_UNIT_LEN = 30;

enum class TSpeed : sdleasygui::t_type
{
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
};

enum class TDisplay : sdleasygui::t_type
{
    Main,
    Option,
    Game,
    Robby,
    Exit,
    None
};

enum class TFigureClass : sdleasygui::t_type
{
    L=0,
    Z,
    I,
    O,
    T,
    S,
    J,
    Begin = L,
    End = T
};

enum class TFigureType : sdleasygui::t_type
{
    A,
    B,
    C,
    D,
    None,
    Begin = A,
    End = D
};

enum class TMap : sdleasygui::t_type
{
    Rain,
    Praymid,
    Randomly,
    Stairway,
    Snow,
    Snail,
    None
};

enum UnitType
{
    Fill = 1 << 0,
    Figure = 1 << 1,
    Ghost = 1 << 2,
    Empty = 1 << 3
};


enum TetrisEvent{

    TETRIS_EVENT_FIGURETIMER = 0x0000,
};

typedef struct UserEvent {
    static  sdleasygui::t_eventType SDLEASYGUI_EVENT;
}UserEvent;

SDL_TETRIS_END


#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

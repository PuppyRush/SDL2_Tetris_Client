//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_TPROPERTY_H
#define TERIS_FIGURE_CLASS_TPROPERTY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TDefine.h"
#include "GameInterface/include/Event.h"

SDL_TETRIS_BEGIN

constexpr const sdleasygui::t_size OTHER_USER_COUNT = 6;

constexpr const sdleasygui::t_size UNIT_LENGTH = 30;
constexpr const sdleasygui::t_size OTHER_UNIT_LENGTH = 10;
constexpr const sdleasygui::t_size GAMEBOARD_GAP = 50;
constexpr const sdleasygui::t_size GAMEBOARD_WIDTH_COUNT = 10;
constexpr const sdleasygui::t_size GAMEBOARD_HEIGHT_COUNT = 20;

constexpr const sdleasygui::t_size GAMEBOARD_DISPLAY_HEIGHT = UNIT_LENGTH * GAMEBOARD_HEIGHT_COUNT;
constexpr const sdleasygui::t_size GAMEBOARD_DISPLAY_WIDTH = UNIT_LENGTH * GAMEBOARD_WIDTH_COUNT;
constexpr const sdleasygui::t_size OTHER_GAMEBOARD_DISPLAY_HEIGHT = OTHER_UNIT_LENGTH * GAMEBOARD_HEIGHT_COUNT;
constexpr const sdleasygui::t_size OTHER_GAMEBOARD_DISPLAY_WIDTH = OTHER_UNIT_LENGTH * GAMEBOARD_WIDTH_COUNT;

constexpr const sdleasygui::t_size NEXTFIGURE_BOARD_WIDTH_COUNT = 3;
constexpr const sdleasygui::t_size NEXTFIGURE_BOARD_HEIGHT_COUNT = 4;

constexpr const sdleasygui::t_size OTHER_GAMEBOARD_BEGIN_X = 100;
constexpr const sdleasygui::t_size OTHER_GAMEBOARD_BEGIN_Y = 100;
constexpr const sdleasygui::t_size GAMEBOARD_BEGIN_X =
        OTHER_GAMEBOARD_BEGIN_X + (OTHER_GAMEBOARD_DISPLAY_WIDTH + GAMEBOARD_GAP) * 3;
constexpr const sdleasygui::t_size GAMEBOARD_BEGIN_Y = OTHER_GAMEBOARD_BEGIN_Y;

constexpr const sdleasygui::t_size FIGURE_UNIT_LEN = 30;

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
    L = 0,
    Z,
    I,
    O,
    T,
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
    Fixed = 1 << 0,
    Moving = 1 << 1,
    Ghost = 1 << 2,
    Empty = 1 << 3
};

enum TetrisEvent
{

    TETRIS_EVENT_START = game_interface::toUType(sdleasygui::SEG_Event::SEGEVENT_END) + 1,
    TETRIS_EVENT_FIGURETIMER
};

typedef struct UserEvent
{
    static sdleasygui::t_eventType SDLEASYGUI_EVENT;
} UserEvent;

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

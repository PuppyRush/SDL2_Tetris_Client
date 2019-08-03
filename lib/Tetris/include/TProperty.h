//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_TPROPERTY_H
#define TERIS_TPROPERTY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "GameInterface/include/Event.h"
#include "SDL2EasyGUI/include/SEG_Type.h"

namespace tetris_module{

constexpr const seg::t_size OTHER_USER_COUNT = 6;

constexpr const seg::t_size UNIT_LENGTH = 30;
constexpr const seg::t_size OTHER_UNIT_LENGTH = 10;
constexpr const seg::t_size GAMEBOARD_GAP = 50;
constexpr const seg::t_size GAMEBOARD_WIDTH_COUNT = 10;
constexpr const seg::t_size GAMEBOARD_HEIGHT_COUNT = 20;

constexpr const seg::t_size GAMEBOARD_DISPLAY_HEIGHT = UNIT_LENGTH * GAMEBOARD_HEIGHT_COUNT;
constexpr const seg::t_size GAMEBOARD_DISPLAY_WIDTH = UNIT_LENGTH * GAMEBOARD_WIDTH_COUNT;
constexpr const seg::t_size OTHER_GAMEBOARD_DISPLAY_HEIGHT = OTHER_UNIT_LENGTH * GAMEBOARD_HEIGHT_COUNT;
constexpr const seg::t_size OTHER_GAMEBOARD_DISPLAY_WIDTH = OTHER_UNIT_LENGTH * GAMEBOARD_WIDTH_COUNT;

constexpr const seg::t_size NEXTFIGURE_BOARD_WIDTH_COUNT = 3;
constexpr const seg::t_size NEXTFIGURE_BOARD_HEIGHT_COUNT = 4;

constexpr const seg::t_size OTHER_GAMEBOARD_BEGIN_X = 100;
constexpr const seg::t_size OTHER_GAMEBOARD_BEGIN_Y = 100;
constexpr const seg::t_size GAMEBOARD_BEGIN_X =
        OTHER_GAMEBOARD_BEGIN_X + (OTHER_GAMEBOARD_DISPLAY_WIDTH + GAMEBOARD_GAP) * 3;
constexpr const seg::t_size GAMEBOARD_BEGIN_Y = OTHER_GAMEBOARD_BEGIN_Y;

constexpr const seg::t_size FIGURE_UNIT_LEN = 30;

enum class TSpeed : seg::t_type
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

enum class TDisplay : seg::t_type
{
    Main,
    Option,
    Game,
    Robby,
    Exit,
    None
};

enum class TFigureClass : seg::t_type
{
    L = 0,
    Z,
    I,
    O,
    T,
    Begin = L,
    End = T
};

enum class TFigureType : seg::t_type
{
    A,
    B,
    C,
    D,
    None,
    Begin = A,
    End = D
};

enum class TMap : seg::t_type
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


}

#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

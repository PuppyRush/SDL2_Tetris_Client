//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_TPROPERTY_H
#define TERIS_FIGURE_CLASS_TPROPERTY_H

#include "TType.h"

SDL_TETRIS_BEGIN

const t_size UNIT_LENGTH = 30;
const t_size WINDOW_HEIGHT = 900;
const t_size WINDOW_WIDTH = 800;
const t_size GAMEBOARD_WIDTH_COUNT = 10;
const t_size GAMEBOARD_HEIGHT_COUNT = 20;
const t_size GAMEBOARD_DISPLAY_HEIGHT = 800;
const t_size GAMEBOARD_DISPLAY_WIDTH = 600;
const t_size GAMEBOARD_BEGIN_X = 20;
const t_size GAMEBOARD_BEGIN_Y = 20;
const t_size GAMEBOARD_UNIT_LEN = 30;

enum class TOption : t_type
{
    StaticLabel,
    EditLabel,
    RadioButton,
};

enum class TDisplay : t_type
{
    Main,
    Option,
    Game,
    Robby,
    Exit,
    None
};

enum class TMode : t_type
{
    Local,
    Online
};

enum class TColorCode : t_type
{
    red = 0,
    blue,
    orange,
    yellow,
    purple,
    green,
    black,
    white,
    none,
    Begin = red,
    End = green
};

enum class TFigureClass : t_type
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

enum class TFigureType : t_type
{
    A,
    B,
    C,
    D,
    None,
    Begin = A,
    End = D
};

enum class MapType : t_type
{
    Rain,
    Praymid
};

enum UnitType
{
    Fill = 1 << 0,
    Shadow = 1 << 1,
    Empty = 1 << 2
};


SDL_TETRIS_END


#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

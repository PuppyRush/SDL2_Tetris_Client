//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_TPROPERTY_H
#define TERIS_FIGURE_CLASS_TPROPERTY_H

#include "TType.h"

SDL_TETRIS_BEGIN

const t_size BOARD_WIDTH_COUNT = 10;
const t_size BOARD_HEIGHT_COUNT = 20;
const t_size UNIT_LENGTH = 30;
const t_size DISPLAY_HEIGHT = 800;
const t_size DISPLAY_WIDTH = 600;


enum class TDisplay : t_type
{
    Main,
    Option,
    Game,
    Robby
};

enum class TMode : t_type
{
    Local,
    Online
};

enum class TColor : t_type
{
    red = 0,
    blue,
    orange,
    yellow,
    purple,
    green,
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
    Rain
};

enum UnitType
{
    Fill = 1 << 0,
    Shadow = 1 << 1,
    Empty = 1 << 2
};


SDL_TETRIS_END


#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

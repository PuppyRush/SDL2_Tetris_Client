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
const t_size GAMEBOARD_DISPLAY_HEIGHT = UNIT_LENGTH*GAMEBOARD_HEIGHT_COUNT;
const t_size GAMEBOARD_DISPLAY_WIDTH = UNIT_LENGTH*GAMEBOARD_WIDTH_COUNT;
const t_size NEXTFIGURE_BOARD_WIDTH_COUNT = 3;
const t_size NEXTFIGURE_BOARD_HEIGHT_COUNT = 4;
const t_size GAMEBOARD_BEGIN_X = 20;
const t_size GAMEBOARD_BEGIN_Y = 20;
const t_size FIGURE_UNIT_LEN = 30;

enum class TSpeed : t_type
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

enum class TControllKind : t_type
{
    StaticLabel,
    EditLabel,
    Button,
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
    silver,
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

enum class TMap : t_type
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


typedef enum TETRIS_EVENT{

    TETRIS_EVENT_FIGURETIMER = 0x9000,
    SDL_DRAWDISPLAY = 0x9001

}TETRIS_EVENT;



SDL_TETRIS_END


#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

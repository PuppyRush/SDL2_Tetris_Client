//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TSTRUCT_H
#define TETRIS_FIGURE_CLASS_TSTRUCT_H

#include <string>

#include "TType.h"
#include "TProperty.h"

SDL_TETRIS_BEGIN

typedef struct TPoint {
public:
    t_coord x;
    t_coord y;
    t_coord z;

    TPoint()
        : x(0), y(0),z(0) {}

    TPoint(const t_coord& x, const t_coord& y, const t_coord& z=0)
        : x(x), y(y),z(z)
    {}

} TPoint;

typedef struct TFont
{
    //something sdl code..
}TFont;

typedef struct TMenu
{
public:
    TPoint point;
    t_size width;
    t_size height;
    TFont font;
    TColor color;
    std::string name;
    TDisplay display;
    bool enabled;

    TMenu()
    :enabled(true),display(TDisplay::None){}

}Menu;


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H

//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TSTRUCT_H
#define TETRIS_FIGURE_CLASS_TSTRUCT_H

#include <cassert>
#include <string>

#include "TType.h"
#include "TProperty.h"

SDL_TETRIS_BEGIN

typedef struct TColor
{
public:
    TColorCode colorCode;
    t_color r;
    t_color g;
    t_color b;
    TColor(){}
    TColor(const TColorCode code)
    {
        colorCode = code;
        switch(code)
        {
            case TColorCode::black:
                r = 0;
                g = 0;
                b = 0;
                break;
            case TColorCode::white:
                r = 255;
                g = 255;
                b = 255;
                break;
            case TColorCode::red:
                r = 255;
                g = 0;
                b = 0;
                break;
            case TColorCode::green:
                r = 0;
                g = 255;
                b = 0;
                break;
            case TColorCode::blue:
                r = 0;
                g = 0;
                b = 255;
                break;
            default:
                assert(0);
                break;
        }
    }

};

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
    std::string font_name;
    t_size size;
    TColor color;
    TFont(){}
    TFont(const std::string& str, const t_size size, const TColorCode color)
        :font_name(str), size(size), color(color)
    {}
}TFont;

typedef struct TMenu
{
public:
    TPoint point;
    t_size width = 100;
    t_size height = 50;
    TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white};
    TColor background_color = TColorCode::black;
    std::string name = "";
    TDisplay display = TDisplay::None;
    bool enabled = true;
    bool multiselected = false;
    TOption kind = TOption::StaticLabel;
    int group = -1;
    bool carot = false;

    bool clicked = false;

}Menu;


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H

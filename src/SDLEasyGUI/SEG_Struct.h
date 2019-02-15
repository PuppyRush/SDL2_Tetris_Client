//
// Created by chaed on 18. 12. 22.
//

#ifndef SDLEASYGUIDE_TSTRUCT_H
#define SDLEASYGUIDE_TSTRUCT_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "SEG_Type.h"
#include "SEG_Property.h"

typedef struct DisplayInfo
{
    t_display display;
    TLocalMode mode;
    TDisplayMode displayMode;
    t_id id;

}DisplayInfo;

typedef struct TColor
{
public:
    TColorCode colorCode;
    t_color r;
    t_color g;
    t_color b;
    t_color a;
    TColor(){}
    TColor(const TColorCode code, const t_color alhpa = 255)
    {
        colorCode = code;
        switch(code)
        {
            case TColorCode::black:
                r = 0;
                g = 0;
                b = 0;
                break;
            case TColorCode::none:  //pass
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
            case TColorCode::orange:
                r = 255;
                g = 140;
                b = 0;
                break;
            case TColorCode::yellow:
                r = 255;
                g = 255;
                b = 0;
                break;
            case TColorCode::purple:
                r = 127;
                g = 0;
                b = 255;
                break;
            case TColorCode::silver:
                r = 169;
                g = 169;
                b = 169;
                break;
            default:
                std::cerr << "cant found : " <<  static_cast<int>(code) << std::endl;
                assert(0);
                break;
        }
        a = 255;
    }

    static SDL_Color getColor(const TColorCode colorCode)
    {
        TColor col(colorCode);
        SDL_Color color{col.r, col.g, col.b,255};
        return color;
    }

    static const SDL_Color getTransparent()
    {
        TColor col(TColorCode::white);
        SDL_Color color{col.r, col.g, col.b,0};
        return color;
    }
}TColor;

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
    TFont() = default;
    TFont(const std::string& str, const t_size size, const TColorCode color)
        :font_name(str), size(size), color(color)
    {}
}TFont;

typedef struct ControllBasic
{
    t_res    id;
    TPoint point = TPoint(-100,-100);
    t_size depth = 0;
    t_size width = 100;
    t_size height = 50;
    TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white};
    TColor background_color = TColorCode::black;
    std::string name = "";
    t_display display = std::numeric_limits<t_display>::max();
    bool enabled = true;
    bool multiselected = false;
    TControllKind kind = TControllKind::StaticLabel;
    int group = -1;
    bool carot = false;
    bool autoSize = true;
    bool selected = false;

    ControllBasic() = default;
    ControllBasic(const ControllBasic& b)
        :id(b.id), point(b.point), width(b.width), height(b.height)
        ,font(b.font), background_color(b.background_color), name(b.name),
        display(b.display), enabled(b.enabled), multiselected(b.multiselected),
        kind(b.kind), group(b.group), carot(b.carot),
        autoSize(b.autoSize), selected(b.selected), depth(b.depth)
    {
    }

}TControllBasic;

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H

//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TSTRUCT_H
#define TETRIS_FIGURE_CLASS_TSTRUCT_H

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "TType.h"
#include "TProperty.h"

SDL_TETRIS_BEGIN




typedef struct TIPString
{
    TIPString()
    :TIPString({192,168,0,1})
    {

    }

    TIPString(std::initializer_list<size_t> fields)
    {
        assert(fields.size() == 4);
        ip.reserve(16);
        for (size_t b : fields)
        {
            ip.append(std::to_string(static_cast<long>(b)));
            ip.append(".");
        }
        ip.pop_back();
    }

    const char* getIP() const
    {
        return ip.c_str();
    }

    std::string ip;
}TIPString;


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
            default:
                std::cerr << "cant found : " <<  static_cast<int>(code) << std::endl;
                assert(0);
                break;
        }
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

class TOptionManager;
typedef struct TControllBasic
{
    t_id    id;
    TPoint point = TPoint(-100,-100);
    t_size width = 100;
    t_size height = 50;
    TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white};
    TColor background_color = TColorCode::black;
    std::string name = "";
    TDisplay display = TDisplay::None;
    bool enabled = true;
    bool multiselected = false;
    TControllKind kind = TControllKind::StaticLabel;
    int group = -1;
    bool carot = false;
    bool autoSize = true;
    bool selected = false;

    std::vector< std::function<void(TOptionManager& mng, bool isSelected)>> callbackAry;

    TControllBasic() = default;
    TControllBasic(const TControllBasic& b)
        :id(b.id), point(b.point), width(b.width), height(b.height)
        ,font(b.font), background_color(b.background_color), name(b.name),
        display(b.display), enabled(b.enabled), multiselected(b.multiselected),
        kind(b.kind), group(b.group), carot(b.carot),
        autoSize(b.autoSize), selected(b.selected)
    {
    }

}TControllBasic;


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H

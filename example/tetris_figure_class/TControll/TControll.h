//
// Created by chaed on 18. 12. 26.
//

#ifndef TETRIS_FIGURE_CLASS_TCONTROLL_H
#define TETRIS_FIGURE_CLASS_TCONTROLL_H

#include "THeader.h"

SDL_TETRIS_BEGIN

class TControll {

public:

    inline const TPoint &getPoint() const noexcept{
        return point;
    }

    inline void setPoint(const TPoint &point) noexcept{
        TControll::point = point;
    }
    inline const t_size getWidth() const noexcept{
        return width;
    }
    inline void setWidth(t_size width) noexcept{
        TControll::width = width;
    }
    inline const t_size getHeight() const noexcept{
        return height;
    }
    inline void setHeight(t_size height) noexcept{
        TControll::height = height;
    }
    inline const TFont &getFont() const noexcept{
        return font;
    }
    inline void setFont(const TFont &font) noexcept{
        TControll::font = font;
    }
    inline const TColor &getBackground_color() const noexcept{
        return background_color;
    }
    inline void setBackground_color(const TColor &background_color) noexcept{
        TControll::background_color = background_color;
    }
    inline const std::string &getName() const noexcept{
        return name;
    }
    inline void setName(const std::string &name) noexcept{
        TControll::name = name;
    }
    inline const TDisplay getDisplay() const noexcept{
        return display;
    }
    inline void setDisplay(TDisplay display) noexcept{
        TControll::display = display;
    }
    inline const bool isEnabled() const noexcept{
        return enabled;
    }
    inline void setEnabled(bool enabled) noexcept{
        TControll::enabled = enabled;
    }
    inline const bool isMultiselected() const noexcept{
        return multiselected;
    }
    inline void setMultiselected(bool multiselected) noexcept{
        TControll::multiselected = multiselected;
    }
    inline const TOption getKind() const noexcept{
        return kind;
    }
    inline void setKind(TOption kind) noexcept{
        TControll::kind = kind;
    }
    inline const int getGroup() const noexcept{
        return group;
    }
    inline void setGroup(int group) noexcept{
        TControll::group = group;
    }
    inline const bool isCarot() const noexcept{
        return carot;
    }
    inline void setCarot(bool carot) noexcept{
        TControll::carot = carot;
    }
    inline const bool isClicked() const noexcept{
        return clicked;
    }
    inline void setClicked(bool clicked) noexcept{
        TControll::clicked = clicked;
    }

private:
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

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H

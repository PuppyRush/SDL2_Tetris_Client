//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_RADIOBUTTON_H
#define CONTROLLER_RADIOBUTTON_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Controller/Button/ButtonBasic.h"

namespace sdleasygui {

class RadioButtonBuilder;

class RadioButton : public ButtonBasic
{
public:

    virtual ~RadioButton() = default;

    explicit RadioButton(RadioButtonBuilder& bld);


    void setSelected(const bool chk)
    {
        Control::setSelected(chk);
        _drawCheck(chk);
    }

    virtual void initialize() override;

    virtual void onDraw() override final;

private:

    const SEG_Color m_lineColor{ColorCode::red};

    t_size m_thick;

    void _drawCheck(const bool chk);

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;
};

class RadioButtonBuilder : public BorderBuilder
{
public:

    t_size m_thick{5};

    RadioButtonBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
        width(20);
        height(20);
        borderColor(ColorCode::black);
    }

    RadioButtonBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
        width(20);
        height(20);
        borderColor(ColorCode::black);
    }

    virtual ~RadioButtonBuilder() = default;

    RadioButtonBuilder* checkedThick(const size_t thick)
    {
        m_thick = thick;
        return this;
    }

    virtual Control::control_ptr build() final
    {
        return new RadioButton(*this);
    }

private:

    inline ControlBuilder* borderBoundaryType(const BorderBoundaryType type)
    {
        return this;
    }
};

}

#endif //TETRIS_FIGURE_CLASS_TRADIOBUTTON_H

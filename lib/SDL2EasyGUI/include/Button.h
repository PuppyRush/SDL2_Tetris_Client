//
// Created by chaed on 18. 12. 27.
//

#ifndef SDL2EASYGUI_BUTTON_H
#define SDL2EASYGUI_BUTTON_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Control/Button/ButtonBasic.h"

namespace seg {

class ButtonBuilder;

class Button : public ButtonBasic
{

public:
    explicit Button(ButtonBuilder& bld);

    virtual ~Button() = default;

    virtual void initialize() override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

};

class ButtonBuilder : public BorderBuilder
{
public:

    ButtonBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : BorderBuilder(window, point, str)
    {
    }

    ButtonBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : BorderBuilder(window, point, str)
    {
    }

    virtual ~ButtonBuilder() = default;

    virtual Control::control_ptr build() final
    {
        return new Button(*this);
    }

};

}

#endif //SDL2EASYGUI_TBUTTON_H

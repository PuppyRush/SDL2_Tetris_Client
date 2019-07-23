//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTON_H
#define CONTROLLER_BUTTON_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/src/Controller/Button/ButtonBasic.h"

namespace sdleasygui {

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

#endif //TETRIS_FIGURE_CLASS_TBUTTON_H

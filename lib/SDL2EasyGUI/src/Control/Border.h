//
// Created by chaed on 19. 1. 22.
//

#ifndef SDL2EASYGUI_BORDER_H
#define SDL2EASYGUI_BORDER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Control.h"

namespace seg {

class BorderBuilder;

class Border : public Control
{

public:
    virtual ~Border() = default;

    explicit Border(const ControlBuilder& basic);

    virtual void onDraw() override;

protected:

    virtual void initialize() override;

private:

};

class BorderBuilder : public ControlBuilder
{
public:

    BorderBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str)
            : ControlBuilder(window, point, str)
    {
    }

    BorderBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
            : ControlBuilder(window, point, str)
    {
    }

    virtual ~BorderBuilder() = default;

    virtual Control::control_ptr build()
    {
        return new Border(*this);
    }

};

}

#endif //SDL2EASYGUI_TBORDER_H

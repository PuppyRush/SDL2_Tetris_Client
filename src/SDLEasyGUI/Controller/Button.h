//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTON_H
#define CONTROLLER_BUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "ButtonBasic.h"

class ButtonBuilder;
class Button : public ButtonBasic
{

public:
    explicit Button(ButtonBuilder& bld);

    virtual void initialize() override;
    virtual void onDraw() override;

};


class ButtonBuilder : public BorderBuilder
{
public:

    ButtonBuilder(const GraphicInterface::window_ptr window, const Point& point, const std::string& str)
        :BorderBuilder(window,point,str)
    {
    }

    ButtonBuilder(const GraphicInterface::window_ptr window, Point&& point, std::string&& str)
        :BorderBuilder(window,point,str)
    {
    }

    virtual std::shared_ptr<Controll> build() final
    {
        return std::make_shared<Button>(*this );
    }

};



#endif //TETRIS_FIGURE_CLASS_TBUTTON_H

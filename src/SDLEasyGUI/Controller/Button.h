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
    Button(const ButtonBuilder& bld);

    virtual void initialize() override;
    virtual void onDraw();

};


class ButtonBuilder : public ControllBuilder
{
public:

    ButtonBuilder(const GraphicInterface::window_ptr window, const TPoint& point, const std::string& str)
        :ControllBuilder(window,point,str)
    {
    }

    ButtonBuilder(const GraphicInterface::window_ptr window, TPoint&& point, std::string&& str)
        :ControllBuilder(window,point,str)
    {
    }

    virtual std::shared_ptr<Controll> build() final
    {
        return make_shared<Button>(*this);
    }

};



#endif //TETRIS_FIGURE_CLASS_TBUTTON_H

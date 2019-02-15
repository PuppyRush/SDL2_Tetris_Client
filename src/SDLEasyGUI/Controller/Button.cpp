//
// Created by chaed on 18. 12. 27.
//

#include "Button.h"

Button::Button(const ButtonBuilder& bld)
    :ButtonBasic(bld, TControllKind::Button)
{
}

void Button::onDraw()
{
    ButtonBasic::onDraw();
}

void Button::initialize()
{
    Controll::initialize();
}


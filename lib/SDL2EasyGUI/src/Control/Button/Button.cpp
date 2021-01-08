//
// Created by chaed on 18. 12. 27.
//

#include "Button.h"

using namespace seg;

Button::Button(ButtonBuilder& bld)
        : ButtonBasic(bld)
{
    bld.kind(ControlKind::Button);
}

void Button::onDrawBackground()
{
    ButtonBasic::onDrawBackground();
}

void Button::onDraw()
{
    ButtonBasic::onDraw();
}

void Button::initialize()
{
    ButtonBasic::initialize();
}

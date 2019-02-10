//
// Created by chaed on 18. 12. 27.
//

#include "RadioButton.h"

SDL_TETRIS

RadioButton::RadioButton(const ControllBuilder& bld)
    :ButtonBasic(bld, TControllKind::StaticLabel)
{
}


void RadioButton::initialize()
{
    Controll::initialize();
}

void RadioButton::onDraw()
{
    ButtonBasic:onDraw();
}


std::shared_ptr<ButtonBasic> RadioButton::getInstance(const ControllBuilder& bld)
{
    std::shared_ptr<ButtonBasic> inst = std::shared_ptr<RadioButton>(new RadioButton(bld));
    return inst;
}
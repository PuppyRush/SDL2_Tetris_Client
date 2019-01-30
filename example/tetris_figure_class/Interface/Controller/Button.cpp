//
// Created by chaed on 18. 12. 27.
//

#include "Button.h"

SDL_TETRIS

Button::Button(const ControllBuilder& bld)
    :ButtonBasic(bld, TControllKind::Button)
{
}

void Button::initialize()
{
    Controll::initialize();
}

std::shared_ptr<ButtonBasic> Button::getInstance(const ControllBuilder& bld)
{
    std::shared_ptr<ButtonBasic> inst = std::shared_ptr<Button>(new Button(bld));
    return inst;
}


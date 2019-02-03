//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"

SDL_TETRIS


StaticLabel::StaticLabel(const ControllBuilder& bld)
    :ButtonBasic(bld, TControllKind::StaticLabel)
{
}

void StaticLabel::initialize()
{
    Controll::initialize();
}

std::shared_ptr<ButtonBasic> StaticLabel::getInstance(const ControllBuilder& bld)
{
    std::shared_ptr<ButtonBasic> inst = std::shared_ptr<StaticLabel>(new StaticLabel(bld));
    return inst;
}


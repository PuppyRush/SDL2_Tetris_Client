//
// Created by chaed on 18. 12. 27.
//

#include "TRadioButton.h"

SDL_TETRIS

TRadioButton::TRadioButton(const TControllBuilder& bld)
    :TButtonBasic(bld, TControllKind::StaticLabel)
{
}

std::shared_ptr<TButtonBasic> TRadioButton::getInstance(const TControllBuilder& bld)
{
    std::shared_ptr<TButtonBasic> inst = std::shared_ptr<TRadioButton>(new TRadioButton(bld));
    return inst;
}
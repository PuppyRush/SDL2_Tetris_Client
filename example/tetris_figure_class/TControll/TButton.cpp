//
// Created by chaed on 18. 12. 27.
//

#include "TButton.h"

SDL_TETRIS

TButton::TButton(const TControllBuilder& bld)
    :TButtonBasic(bld, TControllKind::Button)
{
}

std::shared_ptr<TButtonBasic> TButton::getInstance(const TControllBuilder& bld)
{
    std::shared_ptr<TButtonBasic> inst = std::shared_ptr<TButton>(new TButton(bld));
    return inst;
}


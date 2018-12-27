//
// Created by chaed on 18. 12. 28.
//

#include "TEditLabel.h"

SDL_TETRIS

TEditLabel::TEditLabel(const TControllBuilder& bld)
    :TControll(bld, TControllKind::Button)
{
}

std::shared_ptr<TControll> TEditLabel::getInstance(const TControllBuilder& bld)
{
    std::shared_ptr<TControll> inst = std::shared_ptr<TEditLabel>(new TEditLabel(bld));
    return inst;
}

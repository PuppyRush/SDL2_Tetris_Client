//
// Created by chaed on 18. 12. 26.
//

#include "TStaticLabel.h"

SDL_TETRIS


TStaticLabel::TStaticLabel(const TControllBuilder& bld)
    :TButtonBasic(bld, TControllKind::StaticLabel)
{
}

std::shared_ptr<TButtonBasic> TStaticLabel::getInstance(const TControllBuilder& bld)
{
    std::shared_ptr<TButtonBasic> inst = std::shared_ptr<TStaticLabel>(new TStaticLabel(bld));
    return inst;
}


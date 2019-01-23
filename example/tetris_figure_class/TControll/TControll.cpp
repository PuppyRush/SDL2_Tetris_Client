//
// Created by chaed on 18. 12. 26.
//

#include "TControll.h"

SDL_TETRIS

TControll::TControll(const TControllBuilder& bld, const TControllKind kind)
{
    m_basic = bld.build();
    m_basic->kind = kind;

}

void TControll::draw() {

}
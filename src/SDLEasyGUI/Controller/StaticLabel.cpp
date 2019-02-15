//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"


StaticLabel::StaticLabel(const ControllBuilder& bld)
    :ButtonBasic(bld, TControllKind::StaticLabel)
{
}

void StaticLabel::onDraw()
{
    ButtonBasic::onDraw();
}


std::shared_ptr<ButtonBasic> StaticLabel::getInstance(const ControllBuilder& bld)
{
    std::shared_ptr<ButtonBasic> inst = std::shared_ptr<StaticLabel>(new StaticLabel(bld));
    return inst;
}


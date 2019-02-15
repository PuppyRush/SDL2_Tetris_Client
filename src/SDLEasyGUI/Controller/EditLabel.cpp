//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"

EditLabel::EditLabel(const ControllBuilder& bld)
    :Controll(bld, TControllKind::Button)
{
}


void EditLabel::initialize()
{
    Controll::initialize();
}

std::shared_ptr<Controll> EditLabel::getInstance(const ControllBuilder& bld)
{
    std::shared_ptr<Controll> inst = std::shared_ptr<EditLabel>(new EditLabel(bld));
    return inst;
}

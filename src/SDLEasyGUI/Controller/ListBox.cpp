//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"


ListBox::ListBox(ListBoxBuilder& bld)
    :Border(bld)
{
    bld.kind(ControllKind::ListBox);
}

void ListBox::onDraw()
{
    Border::onDraw();
}

void ListBox::initialize()
{
    Border::initialize();
}


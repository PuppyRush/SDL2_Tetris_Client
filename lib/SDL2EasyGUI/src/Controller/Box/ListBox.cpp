//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"

using namespace sdleasygui;

ListBox::ListBox(ListBoxBuilder& bld)
        : BoxBasic(bld)
{
    bld.kind(ControllerKind::ListBox);
    m_folded = false;
}

void ListBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    SEG_Point accuPoint = getPoint();
    accuPoint.x += 15;
    accuPoint.y += 10;

    for (const item_ptr item : m_items) {
        TextDrawer textDrawer{renderer, getFont(), accuPoint, item->getString()};
        textDrawer.drawText();

        accuPoint.y += textDrawer.getTextHeight() + 3;
    }
}
//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"
#include <include/SEG_Drawer.h>

using namespace sdleasygui;

ListBox::ListBox(ListBoxBuilder& bld)
        : BoxBasic(bld)
{
    bld.kind(ControlKind::ListBox);
    setFolded(true);
    m_menuMaxCnt = 10;
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
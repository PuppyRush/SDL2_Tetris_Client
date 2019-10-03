//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"
#include <include/SEG_Drawer.h>

using namespace seg;

ListBox::ListBox(ListBoxBuilder& bld)
        : BoxBasic(bld)
{
    bld.kind(ControlKind::ListBox);
    setFolded(true);
    setVisibleMenuCount(10);
}

void ListBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    SEG_Point accuPoint = getPoint();
    accuPoint.x += 15;
    accuPoint.y += 10;

    for (const item_ptr item : getItems()) {
        drawer::TextDrawer textDrawer{renderer, getFont(), accuPoint, item->getString()};
        textDrawer.drawText();

        accuPoint.y += textDrawer.getTextHeight() + 3;
    }
}
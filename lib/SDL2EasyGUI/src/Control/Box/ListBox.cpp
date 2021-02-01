//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"
#include "include/SEG_Drawer.h"

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
    auto renderer = getRenderer();

    SEG_Point ctlPoint = getPoint();
    ctlPoint.x += 5;
    ctlPoint.y += 5;

    for (const item_ptr item : getItems()) {
        drawer::TextDrawer textDrawer{renderer, getFont(), ctlPoint, item->getBoxString()};
        textDrawer.drawText();

        ctlPoint.y += getControlTextHeight() + getMenuGap();
    }

    Base::onDraw();
}
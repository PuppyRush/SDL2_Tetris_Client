//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"
#include "SEG_Drawer.h"

using namespace seg;

StaticLabel::StaticLabel(LabelBasucBuilder& bld)
        : LabelBasic(bld)
{
    bld.kind(ControlKind::StaticLabel);
}

void StaticLabel::onDraw()
{
    LabelBasic::onDraw();
}

void StaticLabel::onDrawBackground()
{

    LabelBasic::onDrawBackground();
}

void StaticLabel::initialize()
{
    drawer::TextDrawer textDrawer{ getWindow()->getSDLRenderer(), getFont(), getPoint(), getLabelString() };

    getBasic()->point.x += 5;
    getBasic()->height = textDrawer.getTextHeight();
    getBasic()->width = textDrawer.getTextWidth();

    LabelBasic::initialize();
}

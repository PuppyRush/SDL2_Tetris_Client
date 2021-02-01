//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"
#include "SEG_Drawer.h"

using namespace seg;

StaticLabel::StaticLabel(LabelBasicBuilder& bld)
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
    LabelBasic::initialize();

    drawer::TextDrawer textDrawer{ getRenderer(), getFont(), getPoint(), getControlText() };

    _getData()->point.x += 5;
    _getData()->height = getControlTextHeight();
    _getData()->width = getControlTextWidth();
}

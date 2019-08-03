//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"
#include <SEG_Drawer.h>

using namespace seg;

StaticLabel::StaticLabel(StaticLabelBuilder& bld)
        : LabelBasic(bld)
{
    bld.kind(ControlKind::StaticLabel);
    m_labelString = bld.getBasic().name;
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
    TextDrawer textDrawer{getWindow()->getSDLRenderer(), getFont(), getPoint(), m_labelString};

    getBasic()->point.x += 5;
    getBasic()->height = textDrawer.getTextHeight();
    getBasic()->width = textDrawer.getTextWidth();

    LabelBasic::initialize();
}

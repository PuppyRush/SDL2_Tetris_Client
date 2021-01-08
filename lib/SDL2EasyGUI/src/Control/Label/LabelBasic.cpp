//
// Created by chaed on 19. 3. 31.
//

#include "LabelBasic.h"
#include "SEG_Drawer.h"

using namespace seg;

LabelBasic::LabelBasic(LabelBasucBuilder& bld)
        : Border(bld), m_labelBasic(bld.m_editBasic)
{

}

void LabelBasic::initialize()
{
    drawer::TextDrawer drawer{getSDLRenderer(), getFont(), getPoint(), getName()};

    setTextWidth(drawer.getTextWidth());
    setTextHeight(drawer.getTextHeight());

    Border::initialize();
}



void LabelBasic::onDraw()
{
    auto point = getPoint();
    drawer::TextDrawer textDrawer{getWindow()->getSDLRenderer(), getFont(), getPoint(), getLabelString()};

    point.x += 5;
    point.y = point.y + (getHeight() - textDrawer.getTextHeight()) / 2;

    textDrawer.setPoint(point);
    textDrawer.drawText();

    Border::onDraw();
}

void LabelBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

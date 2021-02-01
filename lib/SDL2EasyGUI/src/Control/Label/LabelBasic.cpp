//
// Created by chaed on 19. 3. 31.
//

#include "LabelBasic.h"
#include "SEG_Drawer.h"

using namespace seg;

LabelBasic::LabelBasic(LabelBasicBuilder& bld)
        : Border(bld), m_labelBasic(bld.m_editBasic)
{

}

void LabelBasic::initialize()
{
    Border::initialize();

    setControlText(m_labelBasic.editstring);
}

void LabelBasic::onDraw()
{
    auto point = getPoint();
    drawer::TextDrawer textDrawer{ getRenderer(), getFont(), getPoint(), getControlText()};

    point.x += 5;
    point.y = point.y + (getHeight() - getControlTextHeight()) / 2;

    textDrawer.setPoint(point);
    textDrawer.drawText();

    Border::onDraw();
}

void LabelBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

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

    setControlTextPositionX(getPoint().x + 4);
    setControlTextPositionY(getPoint().y + (getHeight() - getControlTextHeight()) / 2);

    setControlText(m_labelBasic.editstring);
}

void LabelBasic::onDraw()
{
    Border::onDraw();
}

void LabelBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

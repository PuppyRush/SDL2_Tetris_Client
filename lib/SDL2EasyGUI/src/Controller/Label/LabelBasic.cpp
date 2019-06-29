//
// Created by chaed on 19. 3. 31.
//

#include "LabelBasic.h"

using namespace sdleasygui;

LabelBasic::LabelBasic(ControllerBuilder& bld)
        : Border(bld)
{

}

void LabelBasic::onDraw()
{
    auto point = getPoint();
    TextDrawer textDrawer{getWindow()->getSDLRenderer(), getFont(), getPoint(), m_labelString};

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

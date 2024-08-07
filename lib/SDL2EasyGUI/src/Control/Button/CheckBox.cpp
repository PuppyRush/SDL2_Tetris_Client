//
// Created by chaed on 19. 4. 27.
//

#include "CheckBox.h"
#include "SEG_Drawer.h"

using namespace seg;

CheckBox::CheckBox(CheckBoxBuilder& bld)
        : ButtonBasic(bld), m_lineThick(bld.m_lineThick), m_type(bld.m_type)
{
    bld.kind(ControlKind::CheckBox);
}

void CheckBox::onDraw()
{
    _drawCheck(isSelected());
    ButtonBasic::onDraw();
}

void CheckBox::onDrawBackground()
{

    ButtonBasic::onDrawBackground();
}

void CheckBox::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    ButtonBasic::onMouseButtonDownEvent(button);
}

void CheckBox::_drawCheck(const bool chk)
{
    switch(m_type)
    {
    case CheckBoxType::vType:
        if (chk) {
            drawer::drawV(getRenderer(), getPosition(), m_lineColor, m_lineThick);
        } else {
            drawer::drawV(getRenderer(), getPosition(), getBackgroundColor(), 0);
        }
        break;
    case CheckBoxType::oType:

        break;
    case CheckBoxType::xType:
        if (chk) {
            drawer::drawX(getRenderer(), getPosition(), m_lineColor, m_lineThick);
        } else {
            drawer::drawX(getRenderer(), getPosition(), getBackgroundColor(), m_lineThick);
        }
        break;
    }


}
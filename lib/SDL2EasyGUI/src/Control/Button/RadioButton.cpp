//
// Created by chaed on 18. 12. 27.
//

#include "RadioButton.h"

#include "include/SEG_Drawer.h"


using namespace seg;

RadioButton::RadioButton(RadioButtonBuilder& bld)
        : ButtonBasic(bld), m_thick(bld.m_thick)
{
    bld.kind(ControlKind::RadioButton);
    bld.checkedThick(bld.getBasic().width * 0.8);
}

void RadioButton::initialize()
{
    ButtonBasic::initialize();
}

void RadioButton::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    ButtonBasic::onMouseButtonDownEvent(button);
}


void RadioButton::_drawCheck(const bool chk)
{
    if (chk) {
        drawer::drawCircle(getRenderer(), getMidPoint(), m_lineColor, m_thick);
    } else {
        drawer::drawCircle(getRenderer(), getMidPoint(), getBackgroundColor(), m_thick);
    }

}

void RadioButton::onDraw()
{
    _drawCheck(isSelected());
    ButtonBasic::onDraw();
}

void RadioButton::setSelected(bool chk)
{
    _drawCheck(chk);
    ButtonBasic::setSelected(chk);
    refresh();
}

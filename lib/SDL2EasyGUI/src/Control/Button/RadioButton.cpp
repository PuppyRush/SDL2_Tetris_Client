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
    Control::initialize();
}

void RadioButton::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    if (button->button == SDL_BUTTON_LEFT && button->state == SDL_PRESSED && isHit({ static_cast<t_coord>( button->x), static_cast<t_coord>(button->y) })) {
        setSelected(!isSelected());
    }
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

void RadioButton::setSelected(const bool chk)
{
    ButtonBasic::setSelected(chk);
    _drawCheck(chk);
}

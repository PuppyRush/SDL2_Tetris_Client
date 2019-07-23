//
// Created by chaed on 18. 12. 27.
//

#include "RadioButton.h"

#include <include/SEG_Drawer.h>


using namespace sdleasygui;

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

void RadioButton::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->button == SDL_BUTTON_LEFT && isHit(button->x, button->y)) {
        setSelected(!isSelected());
    }
}


void RadioButton::_drawCheck(const bool chk)
{
    if (chk) {
        SEG_DrawCircle(getSDLRenderer(), getMidPoint() , getBackgroundColor(), m_thick);
    } else {
        SEG_DrawCircle(getSDLRenderer(), getMidPoint(), m_lineColor , m_thick);
    }

}

void RadioButton::onDraw()
{
    _drawCheck(isSelected());
    ButtonBasic::onDraw();
}

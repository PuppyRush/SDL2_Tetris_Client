//
// Created by chaed on 19. 4. 27.
//

#include "CheckBox.h"
#include "SEG_Drawer.h"

using namespace sdleasygui;

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

void CheckBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->button == SDL_BUTTON_LEFT && isHit(button->x, button->y)) {
        setSelected(!isSelected());
    }
}

void CheckBox::_drawCheck(const bool chk)
{
    switch(m_type)
    {
    case CheckBoxType::vType:
        if (chk) {
            SEG_DrawV(getSDLRenderer(), getPoisition(), getBackgroundColor(), m_lineThick);
        } else {
            SEG_DrawV(getSDLRenderer(), getPoisition(), m_lineColor ,m_lineThick);
        }
        break;
    case CheckBoxType::oType:

        break;
    case CheckBoxType::xType:
        if (chk) {
            SEG_DrawX(getSDLRenderer(), getPoisition(), getBackgroundColor(),m_lineThick);
        } else {
            SEG_DrawX(getSDLRenderer(), getPoisition(), m_lineColor,m_lineThick);
        }
        break;
    }


}
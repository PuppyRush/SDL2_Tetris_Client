//
// Created by chaed on 19. 8. 7..
//


#include "ScrollrableDecorator.h"
#include <include/SEG_Drawer.h>

using namespace seg;

ScrollrableDecorator::ScrollrableDecorator(BoxBasic* ctl)
        : Base(ctl),
          m_scrollbarFocusWidth(14)
{
    m_scrollbarFocusHeight =
            (ctl->getHeight() - getUpperArrowPosition().h - getBelowArrowPosition().h) / ctl->getVisibleMenuMax();
    m_scrollbarFocusPosition = {Base::getPoint().x + Base::getWidth() - m_scrollbarFocusWidth ,
                                Base::getUpperArrowPosition().y + Base::getUpperArrowPosition().h + 2,
                                m_scrollbarFocusWidth, m_scrollbarFocusHeight};

}

void ScrollrableDecorator::onDraw()
{
    Base::onDraw();
    drawScrollbarFocus();
}

void ScrollrableDecorator::onDrawBackground()
{
    Base::onDrawBackground();
}

void ScrollrableDecorator::drawScrollbarFocus()
{
    draw_helper::draw_FilledRoundedRactangel(Base::getSDLRenderer(), this->getPosition(), ColorCode::silver, 3);
}

bool ScrollrableDecorator::isHit(const SEG_Point& point) const _GLIBCXX_NOEXCEPT
{
    return _hitTest(ScrollrableDecorator::getPosition(), point) || Base::isHit(point);
}

void ScrollrableDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (Base::_hitTest(ScrollrableDecorator::getPosition(), {motion->x, motion->y})) {
        draw_helper::draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollrableDecorator::getPosition(), ColorCode::green, 3);
        printf("green!\n");
        //refresh();
    } else {
        draw_helper::draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollrableDecorator::getPosition(), ColorCode::silver, 3);
        Base::onMouseMotionEvent(motion);
        printf("silver!\n");
    }
};

void ScrollrableDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (Base::_hitTest(ScrollrableDecorator::getPosition(), {button->x, button->y})) {

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        }
        if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }

    } else {
        Base::onMouseButtonEvent(button);
    }
}

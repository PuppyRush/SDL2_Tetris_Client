//
// Created by chaed on 19. 8. 7..
//


#include "ScrollrableDecorator.h"
#include "include/SEG_Drawer.h"
#include "GameInterface/include/Logger.h"
#include "SEG_Helper.h"

using namespace seg;

ScrollrableDecorator::ScrollrableDecorator(BoxBasic* ctl)
    : Base(ctl),
    m_staticScrollbarFocusY(Base::getUpperArrowPosition().y + Base::getUpperArrowPosition().h + 2)
{
    t_size scrollbarFocusWidth = 14;
    t_size scrollbarFocusHeight = (ctl->getHeight() - getUpperArrowPosition().h - getBelowArrowPosition().h) / ctl->getVisibleMenuCount();
    
    m_scrollbarFocusPosition = make_sdlrect( Base::getPoint().x + Base::getWidth() - scrollbarFocusWidth + 2,
                                 m_staticScrollbarFocusY,scrollbarFocusWidth -4, scrollbarFocusHeight);

}

ScrollrableDecorator::~ScrollrableDecorator()
{
}

#include <EasyTimer/ElapsedTimer.h>
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
    int remainHeight = Base::getScrollHeight() - getPosition().h;
    int remainMenuCount = getComponent()->getBoxCount() - getComponent()->getVisibleMenuCount() + 1;
    int unitHeight = remainHeight / remainMenuCount;
    if (getComponent()->getBoxStartIndex() > 0)
    {
        setPositionY(m_staticScrollbarFocusY + unitHeight * ( getComponent()->getBoxStartIndex() ));
    }
    else
    {
        setPositionY(m_staticScrollbarFocusY);
    }

    drawer::draw_FilledRoundedRactangel(getRenderer(), this->getPosition(), ColorCode::lightgray, 3);
}

bool ScrollrableDecorator::isHit(const SEG_Point& point) const noexcept
{
    return helper::hitTest(this->getPosition(), point) || Base::isHit(point);
}

void ScrollrableDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (motion->state & SDL_BUTTON_LMASK) {

        setPositionY(motion->y);
        Base::onMouseMotionEvent(motion);
    }
    else {
        drawer::draw_FilledRoundedRactangel(getRenderer(), ScrollrableDecorator::getPosition(),
                                                 ColorCode::green, 3);
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollrableDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (helper::hitTest(ScrollrableDecorator::getPosition(), make_segpoint( button->x, button->y ))) {

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        }
        if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }

    } else {
        Base::onMouseButtonEvent(button);
    }

    refresh();
}

void ScrollrableDecorator::onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
{
    if (wheel->direction == 0) {
        if (wheel->y == -1) {
            getComponent()->setBoxStartIndex(getComponent()->getBoxStartIndex() + 1);
        } else if (wheel->y == 1) {
            getComponent()->setBoxStartIndex(getComponent()->getBoxStartIndex() - 1);
        }
        refresh();
    }

    Base::onMouseWheelEvent(wheel);
}

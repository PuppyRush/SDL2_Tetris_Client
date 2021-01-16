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
    
    m_scrollbarFocusPosition = { static_cast<int>( Base::getPoint().x + Base::getWidth() - scrollbarFocusWidth + 3),
                                 static_cast<int>( m_staticScrollbarFocusY),
                                  static_cast<int>(scrollbarFocusWidth -4), static_cast<int>(scrollbarFocusHeight) };

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
    if (getComponent()->isFolded() == false)
    {
        int remainHeight = Base::getScrollHeight() - getPosition().h;
        int remainMenuCount = getComponent()->getMenuCount() - getComponent()->getVisibleMenuCount() + 1;
        int unitHeight = remainHeight / remainMenuCount;
        if (getComponent()->getMenuStartIndex() > 0)
        {
            setPositionY(m_staticScrollbarFocusY + unitHeight * ( getComponent()->getMenuStartIndex() ));
        }
        else
        {
            setPositionY(m_staticScrollbarFocusY);
        }

        drawer::draw_FilledRoundedRactangel(Base::getSDLRenderer(), this->getPosition(), ColorCode::lightgray, 3);
    }
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
        drawer::draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollrableDecorator::getPosition(),
                                                 ColorCode::green, 3);
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollrableDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (helper::hitTest(ScrollrableDecorator::getPosition(), { static_cast<t_size>(button->x), static_cast<t_size>(button->y) })) {

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
            getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() + 1);
        } else if (wheel->y == 1) {
            getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() - 1);
        }
        refresh();
    }

    Base::onMouseWheelEvent(wheel);
}

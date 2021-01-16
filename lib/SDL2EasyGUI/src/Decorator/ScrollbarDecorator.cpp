//
// Created by chaed on 19. 7. 15.
//

#include <string>

#include "ScrollbarDecorator.h"
#include "GameInterface/include/Logger.h"
#include "include/SEG_Drawer.h"
#include "SEG_Helper.h"

using namespace seg;

ScrollbarDecorator::ScrollbarDecorator(BoxBasic* ctl)
        : Base(ctl)
{
    t_size scrollWidth = 14;

    m_scrollbarPosition = { static_cast<int>(Base::getPoint().x + Base::getWidth() - scrollWidth + 1)
                           ,static_cast<int>(Base::getPoint().y + getComponent()->getMenuHeight() + 2)
                           , static_cast<int>(scrollWidth)
                           , static_cast<int>(Base::getHeight() - getComponent()->getMenuHeight() - 2) };

    m_arrowSize = m_scrollbarPosition.h / 15;

    m_upperArrowPosition = { static_cast<int>(m_scrollbarPosition.x + m_arrowSize / 5 + 2),  static_cast<int>(m_scrollbarPosition.y + 4),
                             static_cast<int>(m_arrowSize),  static_cast<int>(m_arrowSize)};

    m_belowArrowPosition = { static_cast<int>(m_scrollbarPosition.x + m_arrowSize / 5 + 2),
                             static_cast<int>(m_scrollbarPosition.y + m_scrollbarPosition.h - m_arrowSize - 3),
                             static_cast<int>(m_arrowSize),  static_cast<int>(m_arrowSize)};
    
}

ScrollbarDecorator::~ScrollbarDecorator()
{

}

bool ScrollbarDecorator::isHit(const SEG_Point& point) const
{
    return helper::hitTest(this->getPosition(), point) || Base::isHit(point);
}

#include <EasyTimer/ElapsedTimer.h>
void ScrollbarDecorator::onDraw()
{
    Base::onDraw();
    drawScroll();
}

void ScrollbarDecorator::onDrawBackground()
{
    Base::onDrawBackground();
}

void ScrollbarDecorator::drawScroll()
{
    using namespace drawer;
    if (getComponent()->isFolded() == false)
    {
        draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollbarDecorator::getPosition(), ColorCode::darkgray, 6);

        draw_FilledTriangle(Base::getSDLRenderer(),
            { static_cast<t_coord>(m_upperArrowPosition.x + m_upperArrowPosition.w / 2),  static_cast<t_coord>(m_upperArrowPosition.y) },
            { static_cast<t_coord>(m_upperArrowPosition.x),  static_cast<t_coord>(m_upperArrowPosition.y + m_upperArrowPosition.h) },
            { static_cast<t_coord>(m_upperArrowPosition.x + m_upperArrowPosition.w),static_cast<t_coord>(m_upperArrowPosition.y + m_upperArrowPosition.h) }, ColorCode::black);
        draw_FilledTriangle(Base::getSDLRenderer(),
            { static_cast<t_coord>(m_belowArrowPosition.x + m_belowArrowPosition.w),static_cast<t_coord>(m_belowArrowPosition.y) },
            { static_cast<t_coord>(m_belowArrowPosition.x),  static_cast<t_coord>(m_belowArrowPosition.y) },
            { static_cast<t_coord>(m_belowArrowPosition.x + m_belowArrowPosition.w / 2), static_cast<t_coord>(m_belowArrowPosition.y + m_belowArrowPosition.h) },
            ColorCode::black);
    }
}

void ScrollbarDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (helper::hitTest(ScrollbarDecorator::getPosition(), { static_cast<t_size>(motion->x), static_cast<t_size>(motion->y) })) {
    } 
    else {
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollbarDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->state == SDL_PRESSED && helper::hitTest(m_upperArrowPosition, { static_cast<t_size>(button->x), static_cast<t_size>( button->y) })) {
        goUpScrollByUnit();
    } else if (button->state == SDL_PRESSED && helper::hitTest(m_belowArrowPosition, { static_cast<t_size>(button->x), static_cast<t_size>(button->y) })) {
        goDownScrollByUnit();
    } else if (helper::hitTest(ScrollbarDecorator::getPosition(), { static_cast<t_coord>(button->x), static_cast<t_coord>(button->y) })) {

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        } else if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }

    } else {
        Base::onMouseButtonEvent(button);
    }

    onDraw();
}

void ScrollbarDecorator::onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
{
    Base::onMouseWheelEvent(wheel);
}

void ScrollbarDecorator::goUpScrollByUnit()
{
    getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() - m_scrollmovingUnitCount);

}

void ScrollbarDecorator::goDownScrollByUnit()
{
    getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() + m_scrollmovingUnitCount);

}
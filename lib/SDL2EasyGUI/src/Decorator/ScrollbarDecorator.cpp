//
// Created by chaed on 19. 7. 15.
//

#include "ScrollbarDecorator.h"
#include <include/SEG_Drawer.h>

using namespace seg;

ScrollbarDecorator::ScrollbarDecorator(BoxBasic* ctl)
        : Base(ctl),
          m_scrollWidth(14),
          m_scrollHeight(ctl->getHeight() / ctl->getVisibleMenuMax())
{

    m_scrollbarPosition = {Base::getPoint().x + Base::getWidth() - m_scrollWidth, Base::getPoint().y,
                           m_scrollWidth, Base::getHeight()};

    m_arrowSize = m_scrollbarPosition.h / 15;

    m_upperArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 5, m_scrollbarPosition.y,
                            m_arrowSize, m_arrowSize};

    m_belowArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 5,
                            m_scrollbarPosition.y + m_scrollbarPosition.h - m_arrowSize,
                            m_arrowSize, m_arrowSize};

    /*m_scrollbarPosition.y += m_upperArrowPosition.h;
    m_scrollbarPosition.h -= m_belowArrowPosition.h;
*/
}

ScrollbarDecorator::~ScrollbarDecorator()
{

}

bool ScrollbarDecorator::isHit(const SEG_Point& point) const
{
    return _hitTest(this->getPosition(), point) || Base::isHit(point);
}

#include <EasyTimer/ElapsedTimer.h>
void ScrollbarDecorator::onDraw()
{
    using namespace easytimer;
    ElapsedTimer<std::nano> et;
    et.start();
    Base::onDraw();
    drawScroll();
    et.end();
    std::cout << get_duration_string(et.time_duration()) << std::endl;

}

void ScrollbarDecorator::onDrawBackground()
{
    Base::onDrawBackground();
}

void ScrollbarDecorator::drawScroll()
{
    using namespace drawer;

    draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollbarDecorator::getPosition(), ColorCode::darkgray, 5);

    draw_FilledTriangle(Base::getSDLRenderer(),
                        {m_upperArrowPosition.x + m_upperArrowPosition.w / 2, m_upperArrowPosition.y},
                        {m_upperArrowPosition.x, m_upperArrowPosition.y + m_upperArrowPosition.h},
                        {m_upperArrowPosition.x + m_upperArrowPosition.w,
                         m_upperArrowPosition.y + m_upperArrowPosition.h}, ColorCode::black);
    draw_FilledTriangle(Base::getSDLRenderer(),
                        {m_belowArrowPosition.x + m_belowArrowPosition.w,
                         m_belowArrowPosition.y},
                        {m_belowArrowPosition.x, m_belowArrowPosition.y},
                        {m_belowArrowPosition.x + m_belowArrowPosition.w / 2,
                         m_belowArrowPosition.y + m_belowArrowPosition.h},
                        ColorCode::black);
}

void ScrollbarDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (Base::_hitTest(ScrollbarDecorator::getPosition(), {motion->x, motion->y})) {
    } else {
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollbarDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->state == SDL_PRESSED && Base::_hitTest(m_upperArrowPosition, {button->x, button->y})) {
        getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() - 1);
        refresh();
    } else if (button->state == SDL_PRESSED && Base::_hitTest(m_belowArrowPosition, {button->x, button->y})) {
        getComponent()->setMenuStartIndex(getComponent()->getMenuStartIndex() + 1);
        refresh();
    } else if (Base::_hitTest(ScrollbarDecorator::getPosition(), {button->x, button->y})) {

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        } else if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }
        refresh();

    } else {
        Base::onMouseButtonEvent(button);
    }

}

void ScrollbarDecorator::onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
{
    Base::onMouseWheelEvent(wheel);
}

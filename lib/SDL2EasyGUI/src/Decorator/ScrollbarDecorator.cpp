//
// Created by chaed on 19. 7. 15.
//

#include <string>

#include "ScrollbarDecorator.h"
#include "GameInterface/include/Logger.h"
#include "include/SEG_Drawer.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;

ScrollbarDecorator::ScrollbarDecorator(BoxBasic* ctl)
        : Base(ctl)
{
    t_size scrollWidth = 14;

    m_scrollbarPosition = make_sdlrect(Base::getPoint().x + Base::getWidth() - scrollWidth, Base::getPoint().y + getControl()->getMenuHeight()
                                    , scrollWidth, Base::getHeight() - getControl()->getMenuHeight() - 2);

    m_arrowSize = m_scrollbarPosition.h / 15;

    m_upperArrowPosition = make_sdlrect(m_scrollbarPosition.x + m_arrowSize / 5 + 2, m_scrollbarPosition.y + 4,
                             m_arrowSize, m_arrowSize);

    m_belowArrowPosition = make_sdlrect(m_scrollbarPosition.x + m_arrowSize / 5 + 2, m_scrollbarPosition.y + m_scrollbarPosition.h - m_arrowSize - 3,
                             m_arrowSize,  m_arrowSize);
    
}

ScrollbarDecorator::~ScrollbarDecorator()
{

}

void ScrollbarDecorator::initialize()
{
    //Base::initialize();
}

void ScrollbarDecorator::attach()
{
    getControl()->setVisibleMenuWidth(getControl()->getWidth() - getPosition().w - 5);
    Base::attach();
}

void ScrollbarDecorator::detach()
{
    getControl()->setVisibleMenuWidth(getControl()->getWidth() - getPosition().w + 5);
    Base::detach();
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

    draw_FilledRoundedRactangel(getRenderer(), ScrollbarDecorator::getPosition(), ColorCode::darkgray, 6);

    draw_FilledTriangle(getRenderer(),
        make_segpoint(m_upperArrowPosition.x + m_upperArrowPosition.w / 2, m_upperArrowPosition.y),
        make_segpoint(m_upperArrowPosition.x,  m_upperArrowPosition.y + m_upperArrowPosition.h),
        make_segpoint(m_upperArrowPosition.x + m_upperArrowPosition.w, m_upperArrowPosition.y + m_upperArrowPosition.h) , ColorCode::black);
    draw_FilledTriangle(getRenderer(),
        make_segpoint(m_belowArrowPosition.x + m_belowArrowPosition.w,  m_belowArrowPosition.y),
        make_segpoint(m_belowArrowPosition.x,  m_belowArrowPosition.y) ,
        make_segpoint(m_belowArrowPosition.x + m_belowArrowPosition.w / 2, m_belowArrowPosition.y + m_belowArrowPosition.h), ColorCode::black);
}

void ScrollbarDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (helper::hitTest(ScrollbarDecorator::getPosition(), make_segpoint(motion->x, motion->y))) {
    } 
    else {
        Base::onMouseMotionEvent(motion);
    }

    refresh();
};

void ScrollbarDecorator::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    if (button->state == SDL_PRESSED && isHitUpperArrow(button->x, button->y)) {
        goUpScrollByUnit();
    } else if (button->state == SDL_PRESSED && isHitBelowArrow(button->x, button->y)) {
        goDownScrollByUnit();
    } else if (helper::hitTest(ScrollbarDecorator::getPosition(), make_segpoint(button->x, button->y) )) {

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        } else if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }

    } else {
        Base::onMouseButtonDownEvent(button);
    }

    onDraw();
}

void ScrollbarDecorator::onMouseButtonUpEvent(const SDL_MouseButtonEvent* button)
{
    if (helper::hitTest(ScrollbarDecorator::getPosition(), make_segpoint(button->x, button->y))) {
    
    }

    Base::onMouseButtonUpEvent(button);
}

void ScrollbarDecorator::onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
{
    Base::onMouseWheelEvent(wheel);
}

void ScrollbarDecorator::goUpScrollByUnit()
{
    getControl()->setBoxStartIndex(getControl()->getBoxStartIndex() - m_scrollmovingUnitCount);
    SEG_Property prp{ PropertyChange::BoxScrollUp, nullptr };
    onChangeProperty(&prp);
    refresh();
}

void ScrollbarDecorator::goDownScrollByUnit()
{
    getControl()->setBoxStartIndex(getControl()->getBoxStartIndex() + m_scrollmovingUnitCount);
    SEG_Property prp{ PropertyChange::BoxScrollDown, nullptr };
    onChangeProperty(&prp);
    refresh();
}

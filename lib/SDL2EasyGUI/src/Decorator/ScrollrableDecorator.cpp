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
    t_size scrollbarFocusHeight = (ctl->getHeight() - getUpperArrowPosition().h - getBelowArrowPosition().h) / (getComponent()->getBoxCount() - ctl->getVisibleMenuCount());
    
    m_scrollbarFocusPosition = make_sdlrect( Base::getPoint().x + Base::getWidth() - scrollbarFocusWidth + 2,
                                 m_staticScrollbarFocusY,scrollbarFocusWidth -4, scrollbarFocusHeight);
    m_lastY = getPosition().y;

    _setUnitHeight();
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
    drawer::draw_FilledRoundedRactangel(getRenderer(), this->getPosition(), ColorCode::lightgray, 3);
}

bool ScrollrableDecorator::isHit(const SEG_Point& point) const noexcept
{
    return helper::hitTest(this->getPosition(), point) || Base::isHit(point);
}

void ScrollrableDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if ( (motion->state & SDL_BUTTON_LMASK) && (motion->x > (getPosition().x - LIMITED_BOUNDARY_X)) )
    {

        if (getDirection(motion->x, motion->y) == ScrollrableDecorator::Direction::Up && isLimitedUpper(motion->x, motion->y) == false
            && ( motion->y - m_lastY > Base::getUpperArrowPosition().y ))
        {
            setPositionY(getPosition().y - ( m_lastY - motion->y));
        }
        else if (getDirection(motion->x, motion->y) == ScrollrableDecorator::Direction::Down && isLimitedBelow(motion->x, motion->y) == false
            && ( m_lastY - motion->y + getPosition().h) < Base::getBelowArrowPosition().y)
        {
            setPositionY(getPosition().y + (motion->y - m_lastY));
        }

        getComponent()->setBoxStartIndex(getBoxIndexByCurrentBarPostion());

        m_lastY = motion->y;
        
        Base::onMouseMotionEvent(motion);
    }
    else {
        drawer::draw_FilledRoundedRactangel(getRenderer(), ScrollrableDecorator::getPosition(),
                                                 ColorCode::green, 3);
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollrableDecorator::onMouseButtonDownEvent(const SDL_MouseButtonEvent* button)
{
    if (helper::hitTest(ScrollrableDecorator::getPosition(), make_segpoint( button->x, button->y ))) {

        setClickingButton(true);
        m_lastY = button->y;

        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            setBackgroundColor(ColorCode::darkgray);
        }

    } else {

        if (isHitUpperEmpty( make_segpoint( button->x, button->y )))
        {
            goUpScrollByUnit();
        }
        else if (isHitBelowEmpty(make_segpoint(button->x, button->y)))
        {
            goDownScrollByUnit();
        }

  

        Base::onMouseButtonDownEvent(button);
    }

    refresh();
}

void ScrollrableDecorator::onMouseButtonUpEvent(const SDL_MouseButtonEvent* button)
{
    if (helper::hitTest(ScrollrableDecorator::getPosition(), make_segpoint(button->x, button->y))) {
    }
    setClickingButton(false);
    Base::onMouseButtonUpEvent(button);
}

void ScrollrableDecorator::onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
{
    if (wheel->direction == 0) {
        if (wheel->y == -1) {
            goDownScrollByUnit();
        } else if (wheel->y == 1) {
            goUpScrollByUnit();
        }
        refresh();
    }

    Base::onMouseWheelEvent(wheel);
}

bool ScrollrableDecorator::isHitUpperEmpty(SEG_Point point)
{
    if (  (Base::getUpperArrowPosition().y + Base::getUpperArrowPosition().h + 2) < point.y && point.y < getPosition().y
        && (getPosition().x < point.x && point.x < (getPosition().x + getPosition().w -2) ))
        return true;
    else
        return false;
}

bool ScrollrableDecorator::isHitBelowEmpty(SEG_Point point)
{
    if ((getPosition().y < point.y && point.y < Base::getBelowArrowPosition().y)
        && (getPosition().x < point.x && point.x < (getPosition().x + getPosition().w)))
        return true;
    else
        return false;
}

void ScrollrableDecorator::onDetachFocus(const SDL_UserEvent* user)
{
    if (isClickingButton())
    {
        return;
    }
    else
    {
        Base::onDetachFocus(user);
    }
}

void ScrollrableDecorator::refresh()
{

    Base::refresh();
}


void ScrollrableDecorator::goUpScrollByUnit()
{

    Base::goUpScrollByUnit();
}

void ScrollrableDecorator::goDownScrollByUnit()
{

    Base::goDownScrollByUnit();
}

void ScrollrableDecorator::onChangeProperty(const SEG_Property* property)
{
    if (property->property == PropertyChange::BoxItemRemove || property->property == PropertyChange::BoxItemAdd)
    {
        _setUnitHeight();
    }
    else if (property->property == PropertyChange::BoxScrollDown || property->property == PropertyChange::BoxScrollUp)
    {
        if (getComponent()->getBoxStartIndex() > 0)
        {
            setPositionY(m_staticScrollbarFocusY + m_unitHeight * (getComponent()->getBoxStartIndex()));
        }
        else
        {
            setPositionY(m_staticScrollbarFocusY);
        }
    }
}

bool ScrollrableDecorator::isLimitedUpper(t_coord x, t_coord y) const noexcept
{
    return (Base::getUpperArrowPosition().y + Base::getUpperArrowPosition().h + 4) >= getPosition().y ;
}

bool ScrollrableDecorator::isLimitedBelow(t_coord x, t_coord y) const noexcept
{
    return getPosition().y + getPosition().h >= (Base::getBelowArrowPosition().y - 4);
}

ScrollrableDecorator::Direction ScrollrableDecorator::getDirection(t_coord x, t_coord y) const noexcept
{
    return m_lastY < y ? ScrollrableDecorator::Direction::Down : ScrollrableDecorator::Direction::Up;
}

t_size ScrollrableDecorator::getBoxIndexByCurrentBarPostion() const noexcept
{
    return (getPosition().y - m_staticScrollbarFocusY + getPosition().h/1.7 ) / (getPosition().h/1.5);
}



void ScrollrableDecorator::_setUnitHeight()
{
    t_size remainHeight = Base::getScrollHeight() - getPosition().h - getUpperArrowPosition().h - getBelowArrowPosition().h;
    t_size remainMenuCount = getComponent()->getBoxCount() - getComponent()->getVisibleMenuCount() + 1;
    m_unitHeight = remainHeight / remainMenuCount;

}
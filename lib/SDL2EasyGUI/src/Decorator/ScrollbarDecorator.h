//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2EASYGUI_SCROLLBARDECORATOR_H
#define SDL2EASYGUI_SCROLLBARDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Decorator.h"
#include "../SEG_Helper.h"
#include "../Control/Box/BoxBasic.h"
#include "SDL2EasyGUI/include/SEG_Drawer.h"

namespace seg {

class ScrollbarDecorator : public Decorator<BoxBasic>
{
public:

    using Base = Decorator<BoxBasic>;

    explicit ScrollbarDecorator(BoxBasic* ctl);

    virtual ~ScrollbarDecorator();

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onMouseButtonDownEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseButtonUpEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override;

    virtual bool isHit(const SEG_Point& point) const;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void attach() override;

    virtual void detach() override;

    virtual void goUpScrollByUnit();

    virtual void goDownScrollByUnit();

    inline t_size getScrollMoveUnit() const noexcept
    {
        return m_scrollmovingUnitCount;
    }

    inline void setScrollMoveUnit(const t_size unit) noexcept
    {
        m_scrollmovingUnitCount = unit;
    }

    inline t_size getScrollMoveUnitSize() const noexcept
    {
        return m_scrollmovingUnitSize;
    }

    inline void setScrollMoveUnitSize(const t_size size) noexcept
    {
        m_scrollmovingUnitSize = size;
    }

    bool isHitUpperArrow(const t_coord x, const t_coord y) const noexcept
    {
        return helper::hitTest(getUpperArrowPosition(), x, y );
    }

    bool isHitBelowArrow(const t_coord x, const t_coord y) const noexcept
    {
        return helper::hitTest(getBelowArrowPosition(), x, y );
    }

protected:

    void drawScroll();

    virtual void initialize() override;

    inline virtual SDL_Rect getPosition() const noexcept override
    { return m_scrollbarPosition; }

    inline SDL_Rect getUpperArrowPosition() const noexcept
    { return m_upperArrowPosition; }

    inline SDL_Rect getBelowArrowPosition() const noexcept
    { return m_belowArrowPosition; }

    inline t_size getScrollHeight() const noexcept
    {
        return m_scrollbarPosition.h;
    }

    inline t_size getScrollWidth() const noexcept
    {
        return m_scrollbarPosition.w;
    }

    inline t_size getScrollStartY() const noexcept
    {
        return m_upperArrowPosition.y + m_upperArrowPosition.h;
    }

    inline t_size getScrollEndY() const noexcept
    {
        return m_belowArrowPosition.y;
    }

private:
    t_size m_arrowSize = 0;
    t_size m_scrollmovingUnitCount = 1;
    t_size m_scrollmovingUnitSize = 10;
    SDL_Rect m_scrollbarPosition;
    SDL_Rect m_upperArrowPosition;
    SDL_Rect m_belowArrowPosition;
};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLBARDECORATOR_H

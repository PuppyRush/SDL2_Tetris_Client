//
// Created by chaed on 19. 7. 30.
//

#ifndef SDL2EASYGUI_SCROLLRABLEDECORATOR_H
#define SDL2EASYGUI_SCROLLRABLEDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "ScrollbarDecorator.h"

namespace seg {

class ScrollrableDecorator : public ScrollbarDecorator
{

enum class Direction
{
    Up,
    Down
};

public:

    using Base = ScrollbarDecorator;
    using item_type = BoxBasic::item_type;
    using item_ptr = BoxBasic::item_ptr;

    explicit ScrollrableDecorator(BoxBasic* ctl);

    virtual ~ScrollrableDecorator();

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onMouseButtonDownEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseButtonUpEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void onDetachFocus(const SDL_UserEvent* user) override;

    virtual void refresh() override;

    virtual void goUpScrollByUnit() override;

    virtual void goDownScrollByUnit() override;

    virtual void onChangeProperty(const SEG_Property* property) override;
    
    t_size getBoxIndexByCurrentBarPostion() const noexcept;

protected:


	inline virtual void setPosition(const SDL_Rect rect) noexcept
    { m_scrollbarFocusPosition = rect; }

    inline virtual SDL_Rect getPosition() const noexcept override
    { return m_scrollbarFocusPosition; }

    inline void setPositionY(const t_size value) noexcept
    {
        m_scrollbarFocusPosition.y = value;
    }

    inline void setClickingButton(const bool b) noexcept
    {
        m_clickingButton = b;
    }

    inline bool isClickingButton() const noexcept
    {
        return m_clickingButton;
    }


    inline bool isHitUpperEmpty(SEG_Point point);

    inline bool isHitBelowEmpty(SEG_Point point);

    void drawScrollbarFocus();

    inline virtual bool isHit(const SEG_Point& point) const noexcept;
    
    inline bool isLimitedUpper(t_coord x, t_coord y) const noexcept;

    inline bool isLimitedBelow(t_coord x, t_coord y) const noexcept;

    inline Direction getDirection(t_coord x, t_coord y) const noexcept;

private:

    void _setUnitHeight();

private:

    bool m_clickingButton = false;
    t_size m_unitHeight = 0;
    SDL_Rect m_scrollbarFocusPosition;
    t_coord m_lastY = INVALID_COORD;
    const t_coord m_staticScrollbarFocusY;
    const t_coord LIMITED_BOUNDARY_X = 15;
};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLRABLEDECORATOR_H

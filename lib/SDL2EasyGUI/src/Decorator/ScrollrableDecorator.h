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
public:

    using Base = ScrollbarDecorator;

    explicit ScrollrableDecorator(BoxBasic* ctl);

    virtual ~ScrollrableDecorator();

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;


protected:

	inline virtual void setPosition(const SDL_Rect rect) noexcept
    { m_scrollbarFocusPosition = rect; }

    inline virtual SDL_Rect getPosition() const noexcept override
    { return m_scrollbarFocusPosition; }

    inline void setPositionY(const t_size value) noexcept
    {
        m_scrollbarFocusPosition.y = value;
    }

    void drawScrollbarFocus();

    virtual bool isHit(const SEG_Point& point) const noexcept;
    

private:

    SDL_Rect m_scrollbarFocusPosition;
    const t_coord m_staticScrollbarFocusY;

    t_size m_scrollIndex;
    const t_size m_scrollStartX = 0;
};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLRABLEDECORATOR_H

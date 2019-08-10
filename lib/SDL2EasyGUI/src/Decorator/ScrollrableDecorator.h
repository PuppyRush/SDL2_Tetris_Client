//
// Created by chaed on 19. 7. 30.
//

#ifndef SDL2_TETRIS_CLIENT_SCROLLRABLEDECORATOR_H
#define SDL2_TETRIS_CLIENT_SCROLLRABLEDECORATOR_H

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

protected:

    inline virtual void setPosition(const SDL_Rect rect) _GLIBCXX_NOEXCEPT
    { m_scrollbarFocusPosition = rect; }

    inline virtual SDL_Rect getPosition() const _GLIBCXX_NOEXCEPT override
    { return m_scrollbarFocusPosition; }

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    void drawScrollbarFocus();

    virtual bool isHit(const SEG_Point& point) const _GLIBCXX_NOEXCEPT;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

private:

    SDL_Rect m_scrollbarFocusPosition;
    t_coord m_beginY;
    t_coord m_endY;

    t_size m_scrollbarFocusHeight;
    t_size m_scrollbarFocusWidth;
    t_size m_scrollIndex;
    const t_size m_scrollStartX = 0;
};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLRABLEDECORATOR_H

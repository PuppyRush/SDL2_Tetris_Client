//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2_TETRIS_CLIENT_SCROLLBARDECORATOR_H
#define SDL2_TETRIS_CLIENT_SCROLLBARDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Decorator.h"
#include "../Controller/Box/BoxBasic.h"
#include <SDL2EasyGUI/include/SEG_Drawer.h>

namespace seg {

class ScrollbarDecorator : public Decorator<BoxBasic>
{
public:

    using Base = Decorator<BoxBasic>;

    explicit ScrollbarDecorator(BoxBasic* ctl);

protected:

    virtual bool isHit(const SEG_Point& point) const;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    void drawScroll();

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override;

    inline virtual SDL_Rect getPosition() const _GLIBCXX_NOEXCEPT override
    { return m_scrollbarPosition; }

    inline SDL_Rect getUpperArrowPosition() const _GLIBCXX_NOEXCEPT
    { return m_upperArrowPosition; }

    inline SDL_Rect getBelowArrowPosition() const _GLIBCXX_NOEXCEPT
    { return m_belowArrowPosition; }

private:
    t_size m_arrowSize;
    SDL_Rect m_scrollbarPosition;
    SDL_Rect m_upperArrowPosition;
    SDL_Rect m_belowArrowPosition;

    t_size m_scrollHeight;
    t_size m_scrollWidth;

};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLBARDECORATOR_H

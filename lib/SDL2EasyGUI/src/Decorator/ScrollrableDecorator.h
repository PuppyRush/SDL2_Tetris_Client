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

    ScrollrableDecorator(BoxBasic* ctl)
            : Base(ctl),
              m_scrollbarFocusWidth(14)
    {
        m_scrollbarFocusHeight =
                (ctl->getHeight() - getUpperArrowPosition().h - getBelowArrowPosition().h) / ctl->getVisibleMenuMax();
        m_scrollbarFocusPosition = {Base::getPoint().x + Base::getWidth() - m_scrollbarFocusWidth * 1.1,
                                    Base::getUpperArrowPosition().y + Base::getUpperArrowPosition().h + 2,
                                    m_scrollbarFocusWidth, m_scrollbarFocusHeight};

    }

protected:

    inline virtual void setPosition(const SDL_Rect rect) _GLIBCXX_NOEXCEPT
    {
        m_scrollbarFocusPosition = rect;
    }

    inline virtual SDL_Rect getPoisition() const _GLIBCXX_NOEXCEPT
    {
        return m_scrollbarFocusPosition;
    }

    virtual void onDraw() override
    {
        Base::onDraw();
        drawScrollbarFocus();
    }

    virtual void onDrawBackground() override
    {
        Base::onDrawBackground();
    }

    void drawScrollbarFocus()
    {
        draw_helper::draw_FilledRoundedRactangel(Base::getSDLRenderer(), this->getPosition(), ColorCode::green, 3);
    }

    virtual bool isHit(const SEG_Point& point) const
    {
        return _hitTest(this->getPosition(), point) || Base::isHit(point);
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    {
        if (this->isHit({motion->x, motion->y})) {
            draw_helper::draw_FilledRoundedRactangel(Base::getSDLRenderer(), this->getPosition(), ColorCode::green, 3);
            refresh();
        } else {
            Base::onMouseMotionEvent(motion);
        }
    };

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override
    {
        if (this->isHit({button->x, button->y})) {

            if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
                Base::setBackgroundColor(ColorCode::darkgray);
            }
            if (button->state == SDL_RELEASED) {
                Base::setBackgroundColor(ColorCode::lightgray);
            }

        } else {
            Base::onMouseButtonEvent(button);
        }
    }

    inline virtual SDL_Rect getPosition() const _GLIBCXX_NOEXCEPT override
    { return m_scrollbarFocusPosition; }

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

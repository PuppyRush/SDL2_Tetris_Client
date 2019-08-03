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

    ScrollbarDecorator(BoxBasic* ctl)
            : Base(ctl),
              m_scrollWidth(14),
              m_scrollHeight(ctl->getHeight() / ctl->getVisibleMenuMax())
    {

        m_scrollbarPosition = {Base::getPoint().x + Base::getWidth() - m_scrollWidth, Base::getPoint().y,
                               m_scrollWidth, Base::getHeight()};

        m_arrowSize = m_scrollbarPosition.h / 15;

        m_upperArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 6, m_scrollbarPosition.y,
                                m_arrowSize, m_arrowSize};

        m_belowArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 6,
                                m_scrollbarPosition.y + m_scrollbarPosition.h - m_arrowSize,
                                m_arrowSize, m_arrowSize};

    }

protected:

    virtual bool isHit(const SEG_Point& point) const
    {
        return _hitTest(this->getPosition(), point) || Base::isHit(point);
    }

    virtual void onDraw() override
    {
        Base::onDraw();
        drawScroll();
    }

    virtual void onDrawBackground() override
    {
        Base::onDrawBackground();
    }

    void drawScroll()
    {
        using namespace draw_helper;

        draw_FilledRoundedRactangel(Base::getSDLRenderer(), this->getPosition(), ColorCode::darkgray, 0);

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

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    {
        if (this->isHit({motion->x, motion->y})) {

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

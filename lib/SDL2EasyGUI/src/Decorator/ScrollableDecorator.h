//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2_TETRIS_CLIENT_SCROLLABLEDECORATOR_H
#define SDL2_TETRIS_CLIENT_SCROLLABLEDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Decorator.h"

namespace sdleasygui {

class ScrollableDecorator : public Decorator
{
public:
    ScrollableDecorator(Control*, int scrollWidth);

private:

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    void drawScroll();

    t_size m_scrollWidth;
};

}

#endif //SDL2_TETRIS_CLIENT_SCROLLABLEDECORATOR_H

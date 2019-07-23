//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2_TETRIS_CLIENT_BORDERDECORATOR_H
#define SDL2_TETRIS_CLIENT_BORDERDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Decorator.h"

namespace sdleasygui {

class BorderDecorator : public Decorator
{
public:
    BorderDecorator(Control*, int borderWidth);

private:

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    void drawBorder();

    t_size m_borderWidth;
};

}

#endif //SDL2_TETRIS_CLIENT_BORDERDECORATOR_H

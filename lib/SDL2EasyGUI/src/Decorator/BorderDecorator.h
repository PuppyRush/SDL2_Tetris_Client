//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2EASYGUI_BORDERDECORATOR_H
#define SDL2EASYGUI_BORDERDECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Decorator.h"

namespace seg {

template <class T>
class BorderDecorator : public Decorator<T>
{
public:

    using Base = Decorator<T>;

    BorderDecorator(T* gi, int borderWidth)
            :Decorator<T>(gi), m_borderWidth(borderWidth)
    {
    }

private:

    void onDraw()
    {
        Base::onDraw();
        drawBorder();
    }

    void onDrawBackground()
    {
        Base::onDrawBackground();
    }

    void  drawBorder()
    {



    }


    t_size m_borderWidth;
};

}

#endif //SDL2_TETRIS_CLIENT_BORDERDECORATOR_H

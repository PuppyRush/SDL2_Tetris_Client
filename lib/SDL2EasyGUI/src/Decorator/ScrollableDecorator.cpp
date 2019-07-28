//
// Created by chaed on 19. 7. 15.
//

#include "ScrollableDecorator.h"

#include <include/SEG_Drawer.h>

using namespace sdleasygui;

ScrollableDecorator::ScrollableDecorator(Control* gi, int scrollWidth)
        :Decorator(gi), m_scrollWidth(scrollWidth)
{

}


void ScrollableDecorator::onDraw()
{
    Decorator::onDraw();
    drawScroll();
}

void ScrollableDecorator::onDrawBackground()
{
    Decorator::onDrawBackground();
}

void ScrollableDecorator::drawScroll()
{

    const t_size scrollWidth = 15;

    const SDL_Rect rect{getPoint().x + getWidth() - scrollWidth - 1, getPoint().y,
                        scrollWidth, getHeight()};

    SEG_DrawRoundedRactangel(getSDLRenderer(),rect, ColorCode::darkgray, 10);


}
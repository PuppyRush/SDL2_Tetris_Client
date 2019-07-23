//
// Created by chaed on 19. 7. 15.
//

#include "BorderDecorator.h"

using namespace sdleasygui;

BorderDecorator::BorderDecorator(Control* gi, int borderWidth)
        :Decorator(gi), m_borderWidth(borderWidth)
{

}


void BorderDecorator::onDraw()
{
    Decorator::onDraw();
    drawBorder();
}

void BorderDecorator::onDrawBackground()
{
    Decorator::onDrawBackground();
}

void BorderDecorator::drawBorder()
{



}
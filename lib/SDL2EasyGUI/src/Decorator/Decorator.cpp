//
// Created by chaed on 19. 7. 15.
//

#include "Decorator.h"

using namespace sdleasygui;

Decorator::Decorator(Control* gi)
    :m_graphic(gi), Control(gi)
{

}

void Decorator::onDraw()
{
    m_graphic->onDraw();
}

void Decorator::onDrawBackground()
{
    m_graphic->onDrawBackground();
}

void Decorator::refresh()
{
    m_graphic->refresh();
}

void Decorator::resize()
{
    m_graphic->resize();
}
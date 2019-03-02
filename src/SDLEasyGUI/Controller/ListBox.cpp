//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"

using namespace sdleasygui;

ListBox::ListBox(ListBoxBuilder& bld)
    :Border(bld)
{
    bld.kind(ControllKind::ListBox);
}

void ListBox::appendItem(const std::string& str)
{
    m_menus.push_back(str);
}

void ListBox::onDraw()
{
    SDL_Rect rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};
    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick()*2)+1;
    rect.w = (rect.w - getBorderThick()*2)+1;

    drawBackground(rect, getBackgroundColor());

    Border::onDraw();
}

void ListBox::initialize()
{
    Border::initialize();
}


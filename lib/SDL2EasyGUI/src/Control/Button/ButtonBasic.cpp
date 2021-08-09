//
// Created by chaed on 18. 12. 27.
//

#include "ButtonBasic.h"
#include "include/SEG_Drawer.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;

ButtonBasic::ButtonBasic(ControlBuilder& bld)
        : Border(bld)
{

}

void ButtonBasic::onDraw()
{
    auto renderer = getRenderer();

    SDL_Rect rect;
    if (getAutoSize()) {
        rect = make_sdlrect(getPoint().x - 20,getPoint().y, getControlTextWidth() * 1.2, getControlTextHeight() * 1.4);
    } else {
        rect = make_sdlrect(getPoint().x, getPoint().y, getWidth(), getHeight());
    }

    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick() * 2) + 1;
    rect.w = (rect.w - getBorderThick() * 2) + 1;


    _drawCarot();
    Border::onDraw();
}

void ButtonBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

void ButtonBasic::initialize()
{
    Border::initialize();

}

void ButtonBasic::_drawCarot()
{
    auto renderer = getRenderer();

    if (isSelected() && isCarot()) {
        if (GroupControlManager::getInstance().isSelected(getGroup(), getId())) {
            SDL_Rect rect = make_sdlrect( getPoint().x - 5, getPoint().y - 5, getWidth() + 10 , getHeight() + 10);

            const auto& linecolor = drawer::getColor(ColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
            refresh();
        }
    }
}

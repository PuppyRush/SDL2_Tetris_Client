//
// Created by chaed on 18. 12. 27.
//

#include "ButtonBasic.h"
#include <include/SEG_Drawer.h>

using namespace seg;

ButtonBasic::ButtonBasic(ControlBuilder& bld)
        : Border(bld)
{

}

void ButtonBasic::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    SDL_Rect rect;
    if (getAutoSize()) {
        rect = SDL_Rect{ static_cast<int>(getPoint().x - 20),
                        static_cast<int>(getPoint().y),
                        static_cast<int>(getTextWidth() * 1.2),
                        static_cast<int>(getTextHeight() * 1.4)};
    } else {
        rect = SDL_Rect{ static_cast<int>(getPoint().x), static_cast<int>(getPoint().y), static_cast<int>(getWidth()), static_cast<int>(getHeight()) };
    }

    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick() * 2) + 1;
    rect.w = (rect.w - getBorderThick() * 2) + 1;

    SEG_Point point{static_cast<t_coord>(getPoint().x + (getWidth() - getTextWidth()) / 2),
                    static_cast<t_coord>(getPoint().y + (getHeight() - getTextHeight()) / 2)};


    drawer::TextDrawer drawer{getSDLRenderer(), getFont(), point, getName()};
    drawer.drawText();

    _drawCarot();
    Border::onDraw();
}

void ButtonBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

void ButtonBasic::initialize()
{
    drawer::TextDrawer drawer{getSDLRenderer(), getFont(), getPoint(), getName()};

    setTextWidth(drawer.getTextWidth());
    setTextHeight(drawer.getTextHeight());

    Border::initialize();
}

void ButtonBasic::_drawCarot()
{
    auto renderer = getWindow()->getSDLRenderer();

    if (isSelected() && isCarot()) {
        if (GroupControlManager::getInstance().isSelected(getGroup(), getId())) {
            SDL_Rect rect{ static_cast<int>( getPoint().x - 5), static_cast<int>( getPoint().y - 5), static_cast<int>( getWidth() + 10) , static_cast<int>( getHeight() + 10)};

            const auto& linecolor = drawer::getColor(ColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

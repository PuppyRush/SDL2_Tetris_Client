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
        rect = SDL_Rect{getPoint().x - 20,
                        getPoint().y,
                        static_cast<int>(m_textWidth * 1.2),
                        static_cast<int>(m_textHeight * 1.4)};
    } else {
        rect = SDL_Rect{getPoint().x, getPoint().y, getWidth(), getHeight()};
    }

    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick() * 2) + 1;
    rect.w = (rect.w - getBorderThick() * 2) + 1;

    SEG_Point point{static_cast<int>(getPoint().x + (getWidth() - m_textWidth) / 2),
                    static_cast<int>(getPoint().y + (getHeight() - m_textHeight) / 2)};


    TextDrawer drawer{getSDLRenderer(), getFont(), point, getName()};
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
    TextDrawer drawer{getSDLRenderer(), getFont(), getPoint(), getName()};

    m_textWidth = drawer.getTextWidth();
    m_textHeight = drawer.getTextHeight();

    Border::initialize();
}

void ButtonBasic::_drawCarot()
{
    auto renderer = getWindow()->getSDLRenderer();

    if (isSelected() && isCarot()) {
        if (GroupControlManager::getInstance().isSelected(getGroup(), getResourceId())) {
            SDL_Rect rect{getPoint().x - 5, getPoint().y - 5, getWidth() + 10, getHeight() + 10};

            const auto& linecolor = SEG_Color::getColor(ColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

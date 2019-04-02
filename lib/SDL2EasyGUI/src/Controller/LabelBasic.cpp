//
// Created by chaed on 19. 3. 31.
//

#include "LabelBasic.h"

using namespace sdleasygui;

LabelBasic::LabelBasic(ControllBuilder& bld)
    :Border(bld)
{

}

void LabelBasic::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();
    TextDrawer textDrawer{renderer, getFont(), m_labelString};
    auto textSurface = textDrawer.getTextSurface();

    if(textSurface)
    {
        auto texture = textDrawer.getTexture();

        m_textWidth = textDrawer.getTextWidth();
        m_textHeight = textDrawer.getTextHeight();

        const auto point = getPoint();
        SDL_Rect renderQuad = { static_cast<int>(point.x +5)
            , static_cast<int>(point.y + ( getHeight() - m_textHeight)/2)
            , static_cast<int>(m_textWidth)
            , static_cast<int>(m_textHeight) };
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }

    Border::onDraw();
}

void LabelBasic::onDrawBackground()
{
    auto renderer = getWindow()->getSDLRenderer();

    const auto &back_color = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);

    SDL_Rect rect = SDL_Rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};
    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick()*2)+1;
    rect.w = (rect.w - getBorderThick()*2)+1;

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    Border::onDrawBackground();
}

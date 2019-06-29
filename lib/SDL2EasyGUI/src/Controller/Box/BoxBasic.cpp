//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"

using namespace sdleasygui;

BoxBasic::BoxBasic(ControllerBuilder& bld)
        : Border(bld)
{}

BoxBasic::~BoxBasic()
{}

void BoxBasic::initialize()
{

    Border::initialize();
}

void BoxBasic::onDraw()
{

    Border::onDraw();
}

void BoxBasic::onDrawBackground()
{

    Border::onDrawBackground();
}


void BoxBasic::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (!m_folded && m_selectedMenuIdx > 0) {

        auto renderer = getSDLRenderer();
        const auto& item = m_items.at(m_selectedMenuIdx);
        auto point = getPoint();

        TextDrawer textDrawer{renderer, getFont(), point, item->getString()};

        point.y += textDrawer.getTextHeight() + (MENU_GAP * m_selectedMenuIdx);

        SEG_Color color{ColorCode::lightgray};

        SDL_Rect rect{point.x + 2, point.y + 2,
                      getWidth() - 4, static_cast<int>(textDrawer.getTextHeight()-4)};

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(getSDLRenderer(), color.r, color.g, color.b, 128);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

}

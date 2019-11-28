//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include <include/SEG_Drawer.h>

using namespace seg;

BoxBasic::BoxBasic(ControlBuilder& bld)
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

    if (!isFolded() && m_boundedMenuIndx >= 0) {

        auto renderer = getSDLRenderer();
        const auto& item = m_items.at(m_boundedMenuIndx);
        auto point = getPoint();

        drawer::TextDrawer textDrawer{renderer, getFont(), point, item->getString()};

        point.y += (textDrawer.getTextHeight() * (m_boundedMenuIndx + 1)) + (MENU_GAP * m_boundedMenuIndx);

        SEG_Color color{ColorCode::blue};

        SDL_Rect rect{point.x + 2, point.y + static_cast<int>(textDrawer.getTextHeight()) / 10,
                      getWidth() - 4, static_cast<int>(textDrawer.getTextHeight())};

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(getSDLRenderer(), color.r, color.g, color.b, 128);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


        printf("%d %d\n", m_boundedMenuIndx, point.y);
    }

    Border::onDraw();
}

void BoxBasic::onDrawBackground()
{
    Border::onDrawBackground();
}

void BoxBasic::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (!isFolded()) {

        m_boundedMenuIndx = calcIndexOf(motion->y);
        onDraw();
    }
}

void BoxBasic::removeAll() noexcept
{
    m_items.clear();
}

std::string BoxBasic::getSelectedText()
{
    if (m_items.size() <= m_selectedMenuIdx) {
        throw std::out_of_range{""};
    }

    return m_items.at(m_selectedMenuIdx)->getString();
}

int BoxBasic::calcIndexOf(const t_coord y)
{
    const size_t menuHeight = m_menuHeight + MENU_GAP;

    int test_idx = (y - getPoint().y - menuHeight) / (menuHeight);
    if ((test_idx + m_menuStartIdx) < m_items.size()) {
        return test_idx + getMenuStartIndex();
    }

    return -1;
}



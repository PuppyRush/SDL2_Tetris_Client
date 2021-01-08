//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include "include/SEG_Drawer.h"

using namespace seg;

BoxBasic::BoxBasic(BoxBasicBuilder& bld)
        : Border(bld)
{
    for (auto item : getItems())
    {
        appendItem(item);
    }

    auto point = getPoint();
    drawer::TextDrawer textDrawer{ getSDLRenderer(), getFont(), point, "a" };
    setMenuHeight(textDrawer.getTextHeight());

}

BoxBasic::~BoxBasic()
{}

void BoxBasic::initialize()
{

    Border::initialize();
}

void BoxBasic::onDraw()
{
    // draw highlight
    if (!isFolded() && m_boundedMenuIndx != INVALID_VALUE && (getMenuStartIndex() <= m_boundedMenuIndx && m_boundedMenuIndx <= getMenuStartIndex() + getVisibleMenuCount())) {

        const t_size realBoundedIndex = m_boundedMenuIndx - getMenuStartIndex();
        auto renderer = getSDLRenderer();
        const auto& item = m_items.at(realBoundedIndex);
        auto point = getPoint();

        drawer::TextDrawer textDrawer{renderer, getFont(), point, item->getString()};

        point.y += (textDrawer.getTextHeight() * (realBoundedIndex + 1)) + (MENU_GAP * realBoundedIndex);

        SEG_Color color{ColorCode::blue};

        SDL_Rect rect{ static_cast<int>(point.x + 2), static_cast<int>(point.y + textDrawer.getTextHeight() / 10),
                      static_cast<int>(getWidth() - 4), static_cast<int>(textDrawer.getTextHeight())};

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(getSDLRenderer(), color.r, color.g, color.b, 128);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


        //printf("%d %d\n", m_boundedMenuIndx, point.y);
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
        refresh();
    }
}

void BoxBasic::onDetachFocus(const SDL_UserEvent* user)
{
    setFolded(false);
    refresh();
    Base::onDetachFocus(user);
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
    if (test_idx >= getVisibleMenuCount())
    {
        return -1;
    }

    if ((test_idx + m_menuStartIdx) < m_items.size()) {
        return test_idx + getMenuStartIndex();
    }

    return -1;
}


std::pair<t_size, t_size> BoxBasic::getVisibleRangeIndex() const
{
    return std::make_pair(m_menuStartIdx, m_menuStartIdx + getVisibleMenuCount());
}
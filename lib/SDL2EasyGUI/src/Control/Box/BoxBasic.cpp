//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;

BoxBasic::BoxBasic(BoxBasicBuilder& bld)
        : Border(bld)
{
    if (getControlText().empty() == false)
    {
        //appendItem(std::make_shared<BoxItem>());
    }

    for (const auto& item : bld.getItems())
    {
        appendItem(item);
    }

    auto wh = drawer::getTextSize(getFont().getTTF_Font(), "a");
    setMenuHeight(wh.second);

}

BoxBasic::~BoxBasic()
{}

void BoxBasic::initialize()
{
    for (auto& item : getItems())
    {
        SEG_Point p{ INVALID_COORD, INVALID_COORD, INVALID_COORD };
        item->setTextDrawer(std::make_shared< drawer::TextDrawer>(getRenderer(), getFont(), p, item->getBoxString()));
    }

    if (getItems().empty())
    {
        setControlTextHeight(getMenuHeight());
        setControlTextWidth(getWidth());
    }

    setVisibleMenuWidth(getWidth() - 5);

    Base::initialize();
}

void BoxBasic::onDraw()
{
    // draw highlight
    if (!isFolded() && m_boundedMenuIndx != INVALID_SIZE && (getMenuStartIndex() <= m_boundedMenuIndx && m_boundedMenuIndx <= getMenuStartIndex() + getVisibleMenuCount())) {

        const t_size realBoundedIndex = m_boundedMenuIndx - getMenuStartIndex();
        auto renderer = getRenderer();
        const auto& item = m_items.at(realBoundedIndex);
        auto point = getPoint();

        point.y += (getMenuHeight() * (realBoundedIndex + 1)) + (MENU_GAP * realBoundedIndex);

        SEG_Color color{ColorCode::blue};

        SDL_Rect rect = make_sdlrect(point.x + 2, point.y + getMenuHeight() / 10,
                      getWidth() - 4, getMenuHeight());

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, 128);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


        //printf("%d %d\n", m_boundedMenuIndx, point.y);
    }

    Base::onDraw();
}

void BoxBasic::onDrawBackground()
{
    Base::onDrawBackground();
}

void BoxBasic::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (!isFolded()) {

        m_boundedMenuIndx = calcIndexOf(motion->y);
        refresh();
    }
    Base::onMouseMotionEvent(motion);
}

void BoxBasic::onDetachFocus(const SDL_UserEvent* user)
{
    setFolded(true);
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

    return m_items.at(m_selectedMenuIdx)->getBoxString();
}

t_size BoxBasic::calcIndexOf(const t_coord y)
{
    const size_t menuHeight = m_menuHeight + MENU_GAP;

    int test_idx = (y - getPoint().y - menuHeight) / (menuHeight);
    if (test_idx >= getVisibleMenuCount())
    {
        return INVALID_SIZE;
    }

    if ((test_idx + m_menuStartIdx) < m_items.size()) {
        return test_idx + getMenuStartIndex();
    }

    return INVALID_SIZE;
}

void BoxBasic::appendItem(item_ptr item)
{
    SEG_Point p{ INVALID_COORD, INVALID_COORD, INVALID_COORD };
    item->setTextDrawer(std::make_shared< drawer::TextDrawer>(getRenderer(), getFont(), p, item->getBoxString()));
    item->setIndex(getMenuCount());
    m_items.emplace_back(item);

    autoFitBox(getMenuCount() - 1);
}

void BoxBasic::appendItem(const string_type& str)
{
    auto item = std::make_shared<item_type>(str);
    SEG_Point p{ INVALID_COORD, INVALID_COORD, INVALID_COORD };
    item->setTextDrawer(std::make_shared< drawer::TextDrawer>(getRenderer(), getFont(), p, item->getBoxString()));
    item->setIndex(getMenuCount());
    m_items.emplace_back(item);

    autoFitBox(getMenuCount() - 1);
}

void BoxBasic::autoFitBox(const size_t idx)
{
    if (getMenuCount() <= idx)
    {
        throw std::out_of_range{ "" };
        return;
    }
    if (getItem(idx)->getTextDrawer()->getTextWidth() > getWidth())
    {
        getItem(idx)->getTextDrawer()->setTextWidth(getWidth());
    }
}

t_size BoxBasic::getFittedTextSize(const size_t idx)
{
    if (getMenuCount() <= idx)
    {
        throw std::out_of_range{ "" };
        return 0;
    }

    auto textdrawer = getItem(idx)->getTextDrawer();
    if (textdrawer->getTextWidth() < getVisibleMenuWidth())
    {
        return textdrawer->getTextWidth();
    }
    else
    {
        return getVisibleMenuWidth();
    }

}

std::pair<t_size, t_size> BoxBasic::getvisibleMenuIndexRange()
{
    const t_size endIdx =
        (getMenuStartIndex() + getVisibleMenuCount()) > getItems().size() ? getItems().size() :
        getMenuStartIndex() + getVisibleMenuCount();

    return std::make_pair(getMenuStartIndex(), endIdx);
}

void BoxBasic::recalculateBoxesPosition()
{
    auto point = getPoint();
    point.x = 5;
    point.y += getMenuHeight() + getMenuGap();

    const auto idxpair = getvisibleMenuIndexRange();
    for (t_size i = idxpair.first ; i < idxpair.second ; i++) {

        auto item = getItem(i);
        item->setPosition(make_sdlrect(point.x, point.y, getWidth(), getMenuHeight()));
        item->setTextPosition(make_sdlrect(point.x + 5, point.y, getFittedTextSize(i), getMenuHeight()));
        point.y += getMenuHeight() + getMenuGap();
    }
}
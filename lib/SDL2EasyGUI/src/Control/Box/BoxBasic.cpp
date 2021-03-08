//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;

BoxItem::BoxItem(const BoxBasicItemBuilder& bld)
    : Control(bld)
{
}

BoxItem::BoxItem(BoxBasicItemBuilder&& bld) 
    : Control(bld)
{
}

void BoxItem::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (isHit(make_segpoint(motion->x, motion->y)))
    {
        SEG_Color color{ ColorCode::blue };
        auto rnd = getRenderer();

        SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(rnd, color.r, color.g, color.b, 128);
        SDL_RenderFillRect(rnd, &getConstPosition());
        SDL_RenderDrawRect(rnd, &getConstPosition());
        SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
    }

    Base::onMouseMotionEvent(motion);
}

BoxBasic::BoxBasic(BoxBasicBuilder& bld)
        : Border(bld)
{
   
    for (const auto& item : bld.getItems())
    {
        addItem(item);
    }


    auto wh = drawer::getTextSize(getFont().getTTF_Font(), "a");
    setMenuHeight(wh.second);

}

void BoxBasic::initialize()
{
    setVisibleMenuWidth(getWidth() - 5);

    Base::initialize();
}


std::pair<t_size, t_size> BoxBasic::getvisibleMenuIndexRange()
{
    const t_size endIdx =
        (getBoxStartIndex() + getVisibleMenuCount()) > getBoxCount() ? getBoxCount() :
        getBoxStartIndex() + getVisibleMenuCount();

    return std::make_pair(getBoxStartIndex(), endIdx);
}

void BoxBasic::onEvent(const SDL_Event& event)
{
    Base::onEvent(event);

    for (auto item : getItems())
    {
        item->onEvent(event);
    }
}

void BoxBasic::onDraw()
{
    // draw highlight
    if (_isBoundInMenues()) {

        

    }

    Base::onDraw();
}

void BoxBasic::addItem(const item_ptr item)
{
    m_items.emplace_back(item);

    SEG_Property prop{PropertyChange::BoxItemAdd, nullptr};
    onChangeProperty(&prop);

    autoFitBox(getBoxCount() - 1);
}

void BoxBasic::addItem(const item_type::string_type& str)
{
    BoxBasicItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    m_items.emplace_back(std::make_shared<item_type>(item));

    SEG_Property prop{ PropertyChange::BoxItemAdd, nullptr };
    onChangeProperty(&prop);

    autoFitBox(getBoxCount() - 1);
}

void BoxBasic::addItem(const item_type::string_type&& str)
{
    BoxBasicItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    m_items.emplace_back( std::make_shared<item_type>(item));

    SEG_Property prop{ PropertyChange::BoxItemAdd, nullptr };
    onChangeProperty(&prop);

    autoFitBox(getBoxCount() - 1);
}

BoxBasic::item_ptr BoxBasic::popItem()
{
    auto item = m_items.emplace_back();
    m_items.pop_back();
    
    SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
    onChangeProperty(&prop);

    return item;
}

BoxBasic::item_ptr BoxBasic::removeItem(t_size idx)
{
    auto item = m_items.at(idx);
    auto it = m_items.cbegin();
    std::advance(it, 2);
    m_items.erase(it);

    SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
    onChangeProperty(&prop);

    return item;
}

void BoxBasic::autoFitBox(const size_t idx)
{
    if (getBoxCount() <= idx)
    {
        throw std::out_of_range{ "" };
        return;
    }
    if (getItem(idx)->getControlTextWidth() > getWidth())
    {
        getItem(idx)->setControlTextWidth(getWidth());
    }
}

void BoxBasic::recalculateBoxesPosition()
{
    auto point = getPoint();
    point.x += 5;
    point.y += getMenuHeight();
    const auto idxpair = getvisibleMenuIndexRange();
    for (t_size i = idxpair.first; i < idxpair.second; i++) {

        auto item = getItem(i);
        item->setPosition(make_sdlrect(point.x, point.y, getWidth(), getMenuHeight()));
        //item->setTextPosition(make_sdlrect(point.x + 5, point.y, getFittedTextSize(i), getMenuHeight()));
        point.y += getMenuHeight();
    }
}

bool BoxBasic::_isBoundInMenues()
{
    bool _isBoundInMenues = (getBoxStartIndex() <= getBoundedMenuIndex() && getBoundedMenuIndex() <= getBoxStartIndex() + getVisibleMenuCount());
    return  getBoundedMenuIndex() != INVALID_SIZE && _isBoundInMenues;
}

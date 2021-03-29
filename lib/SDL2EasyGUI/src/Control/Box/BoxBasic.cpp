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
        addComponent(item);
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
        (getBoxStartIndex() + getVisibleMenuCount()) > sizeComponent() ? sizeComponent() :
        getBoxStartIndex() + getVisibleMenuCount();

    return std::make_pair(getBoxStartIndex(), endIdx);
}

void BoxBasic::onEvent(const SDL_Event& event)
{
    Base::onEvent(event);

}

void BoxBasic::onDraw()
{
    // draw highlight
    if (_isBoundInMenues()) {

        const t_size realBoundedIndex = m_boundedMenuIndex - getBoxStartIndex();
        auto renderer = getRenderer();
        const auto& item = atComponent(realBoundedIndex);
        auto point = getPoint();

        point.y += (getMenuHeight() * (realBoundedIndex + 1));

        SEG_Color color{ ColorCode::blue };

        SDL_Rect rect = make_sdlrect(point.x + 2, point.y + getMenuHeight() / 10,
            getWidth() - 4, getMenuHeight());

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, 128);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    }

    Base::onDraw();
}

void BoxBasic::addItem(const item_ptr item)
{
    addComponent(item);

    SEG_Property prop{PropertyChange::BoxItemAdd, nullptr};
    onChangeProperty(&prop);

    autoFitBox(sizeComponent() - 1);
}

void BoxBasic::addItem(const item_type::string_type& str)
{
    BoxBasicItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    addComponent(item.build());

    SEG_Property prop{ PropertyChange::BoxItemAdd, nullptr };
    onChangeProperty(&prop);

    autoFitBox(sizeComponent() - 1);
}

void BoxBasic::addItem(const item_type::string_type&& str)
{
    BoxBasicItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    addComponent(item.build());

    SEG_Property prop{ PropertyChange::BoxItemAdd, nullptr };
    onChangeProperty(&prop);

    autoFitBox(sizeComponent() - 1);
}

BoxBasic::item_ptr BoxBasic::popItem()
{
    auto item = backComponent<BoxItem>();
    popComponent();
    
    SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
    onChangeProperty(&prop);

    return item;
}

BoxBasic::item_ptr BoxBasic::removeItem(t_size idx)
{
    auto item = atComponent<BoxItem>(idx);
    auto it = beginComponent();
    std::advance(it, 2);
    removeComponent(it);

    SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
    onChangeProperty(&prop);

    return item;
}

void BoxBasic::autoFitBox(const size_t idx)
{
    if (sizeComponent() <= idx)
    {
        throw std::out_of_range{ "" };
        return;
    }
    if (atComponent(idx)->getControlTextWidth() > getWidth())
    {
        atComponent(idx)->setControlTextWidth(getWidth());
    }
}

void BoxBasic::recalculateBoxesPosition()
{
    auto point = getPoint();
    point.x += 5;
    point.y += getMenuHeight();
    const auto idxpair = getvisibleMenuIndexRange();
    for (t_size i = idxpair.first; i < idxpair.second; i++) {

        auto item = atComponent(i);
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

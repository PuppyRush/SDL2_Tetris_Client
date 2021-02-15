//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;

BoxItem::BoxItem(BoxBasicItemBuilder& bld)
    : Control(bld)
{

}



BoxBasic::BoxBasic(BoxBasicBuilder& bld)
        : Border(bld)
{
   
    for (const auto& item : bld.getItems())
    {
        appendItem(item);
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

void BoxBasic::onDraw()
{
    Base::onDraw();
}


void BoxBasic::appendItem(const item_ptr& item)
{
    m_items.emplace_back(item);

    autoFitBox(getBoxCount() - 1);
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
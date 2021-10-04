
//
// Created by chaed on 19. 4. 21.
//

#include "BoxBasic.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "../SEG_Helper.h"

using namespace seg;
using namespace seg::helper;



BoxBasic::BoxItemManager::BoxItemManager(BoxBasic& boxBasic)
    :m_boxbasic(boxBasic), m_visibleMenuIndexRange({0,0})
{
}

void BoxBasic::BoxItemManager::push_back(Control* box)
{
    if ( m_boxbasic.getVisibleMenuCount() <= BoxItemManager::getSize())
    {
        return;
    }

    box->setPosition(calculatePosition(m_boxItemAry.size()));
    box->setVisible(true);
    m_boxItemAry.push_back(box);

    box->setPosition(calculatePosition(m_boxItemAry.size()-1));
    
    m_visibleMenuIndexRange.second += 1;
    m_isChanged = true;
}

void BoxBasic::BoxItemManager::pop_back()
{
    m_boxItemAry.back()->setVisible(false);
    m_boxItemAry.pop_back();

    m_visibleMenuIndexRange.second -= 1;
    m_isChanged = true;
}

void BoxBasic::BoxItemManager::push_front(Control* box)
{
    if (m_boxbasic.getVisibleMenuCount() <= m_boxItemAry.size())
    {
        return;
    }

    m_boxItemAry.push_front(box);
    
    t_size i = 0;
    for (auto box : m_boxItemAry)
    {
        box->setPosition(calculatePosition(i));
        i++;
    }

    m_visibleMenuIndexRange.first -= 1;
    box->setVisible(true);

    m_isChanged = true;
}

void BoxBasic::BoxItemManager::pop_front()
{
    m_boxItemAry.front()->setVisible(false);
    m_boxItemAry.pop_front();

    t_size i = 0;
    for (auto box : m_boxItemAry)
    {
        box->setPosition(calculatePosition(i));
        i++;
    }

    m_visibleMenuIndexRange.first += 1;
    m_isChanged = true;
}

void BoxBasic::BoxItemManager::insert(Control* box)
{}

void BoxBasic::BoxItemManager::remove(t_size idx)
{
    auto it = m_boxItemAry.begin();
    t_size i = 0;
    while (i < idx)
    {
        it++;
    }
    auto post_it = m_boxItemAry.erase(it);
    auto end = m_boxItemAry.end();
    for (; post_it != end; post_it++)
    {
        (*post_it)->setPosition(calculatePosition(i));
        i++;
    }
}

void BoxBasic::BoxItemManager::repositionItems()
{
    if (m_isChanged)
    {
        return;
    }
}

void BoxBasic::BoxItemManager::moveDownOf(t_size n)
{
    for (t_size i = 0; i < n && BoxItemManager::getEndIndex() < m_boxbasic.countComponent(); i++)
    {
        auto nextBox = m_boxbasic.atComponent(BoxItemManager::getEndIndex());

        BoxItemManager::pop_front();
        BoxItemManager::push_back(nextBox);
    }
}

void BoxBasic::BoxItemManager::moveUpOf(t_size n)
{
    for (t_size i = 0; i < n && BoxItemManager::getStartIndex() > 0; i++)
    {
        auto prevBox = m_boxbasic.atComponent(BoxItemManager::getStartIndex()-1);

        BoxItemManager::pop_back();
        BoxItemManager::push_front(prevBox);
    }
}

SDL_Rect BoxBasic::BoxItemManager::calculatePosition(int i)
{
    auto point = m_boxbasic.getPoint();
    point.x += 5;
    if (m_boxbasic.m_hasTitleBox)
    {
        point.y += m_boxbasic.getMenuHeight();
    }
    return make_sdlrect(point.x, point.y + (i * m_boxbasic.getMenuHeight()), m_boxbasic.getWidth(), m_boxbasic.getMenuHeight());
}

void BoxBasic::BoxItemManager::divisibleAll()
{
    for (auto item : m_boxItemAry)
    {
        item->setVisible(false);
    }
}

void BoxBasic::BoxItemManager::visibleAll()
{
    for (auto item : m_boxItemAry)
    {
        item->setVisible(true);
    }
}

void BoxBasic::BoxItemManager::calculateVisibleMenuIndexRange()
{
    t_size startIdx = getStartIndex();
    t_size endIdx =
        (startIdx + m_boxbasic.getVisibleMenuCount()) > m_boxbasic.countComponent() ? m_boxbasic.countComponent() - 1 :
        startIdx + m_boxbasic.getVisibleMenuCount();

    m_visibleMenuIndexRange = std::make_pair(startIdx, endIdx);
}


void BoxBasic::BoxItemManager::setStartIndex(t_size mMenuStartIdx)
{
    if (mMenuStartIdx < 0)
    {
        m_visibleMenuIndexRange.first = 0;
        return;
    }
    else if (mMenuStartIdx > (m_boxbasic.countComponent() - m_boxbasic.getVisibleMenuCount()))
    {
        mMenuStartIdx = m_boxbasic.countComponent() - m_boxbasic.getVisibleMenuCount();
    }

    int idxGap = m_visibleMenuIndexRange.first - mMenuStartIdx;
    if (idxGap < 0)
    {
        BoxItemManager::moveDownOf(-idxGap);
    }
    else if(idxGap > 0)
    {
        BoxItemManager::moveUpOf(idxGap);
    }
    else
    {
        // idxGap == 0;
    }
}


BoxBasic::BoxBasic(BoxBasicBuilder& bld)
    : Border(bld), m_boxItemManager({*this})
{
    auto wh = drawer::getTextSize(getFont().getTTF_Font(), "a");
    setMenuHeight(wh.second);

    setVisibleMenuCount(bld.count());

    for (const auto& item : bld.getItems())
    {
        addComponent(item);
    }
}

void BoxBasic::initialize()
{
    setVisibleMenuWidth(getWidth() - 5);
    
    SEG_Point point = make_segpoint( getPoint().x + (getWidth() - getControlTextWidth()) / 2,
                                getPoint().y + (getHeight() - getControlTextHeight()) / 2) ;

    setControlTextPositionX(point.x);
    setControlTextPositionY(point.y);


    Base::initialize();
}

void BoxBasic::goUpScrollByUnit()
{
    _getBoxItemManager().moveUpOf(getScrollMoveUnit());
}

void BoxBasic::goDownScrollByUnit()
{
    _getBoxItemManager().moveDownOf(getScrollMoveUnit());
}

void BoxBasic::onEvent(const SDL_Event& event)
{
    Base::onEvent(event);
}

void BoxBasic::onDraw()
{
    // draw highlight
    if (_isBoundInMenues()) {

        t_size realBoundedIndex = getBoundedMenuIndex() - getBoxStartIndex();
        auto renderer = getRenderer();
        const auto& item = atComponent(realBoundedIndex);
        auto point = getPoint();

        if (hasTitleBox() == true)
        {
            realBoundedIndex += 1;
        }

        point.y += (getMenuHeight() * realBoundedIndex);

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

void BoxBasic::addComponent(const component_ptr& component) 
{
    Base::addComponent(component);
    m_boxItemManager.push_back(component);

    SEG_Property prop{ PropertyChange::BoxItemAdd, nullptr };
    onChangeProperty(&prop);

    _autoFitBox(countComponent() - 1);

}

BoxBasic::iterator BoxBasic::removeComponentFromIndex(t_size idx)
{
    m_boxItemManager.remove(idx);
    return Base::removeComponentFromIndex(idx);
}

BoxBasic::iterator BoxBasic::removeComponent(component_type::unique_type resId)
{
    return Base::removeComponent(resId);
}

BoxBasic::iterator BoxBasic::removeComponent(iterator& it)
{
    auto dist = std::distance(Base::beginComponent(), it);
    m_boxItemManager.remove(dist);

    auto resit = Base::removeComponent(it);
    if (resit != endComponent())
    {    
        SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
        onChangeProperty(&prop);
    }

    
    return resit;
}

void BoxBasic::popComponent() noexcept
{
    Base::popComponent();
    m_boxItemManager.pop_back();

    SEG_Property prop{ PropertyChange::BoxItemRemove, nullptr };
    onChangeProperty(&prop);
}

void BoxBasic::addItem(const item_ptr item)
{
    addComponent(item);
    refresh();
}

void BoxBasic::addItem(const item_type::string_type& str)
{
    BoxItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    addComponent(item.build());
    refresh();
}

void BoxBasic::addItem(item_type::string_type&& str)
{
    BoxItemBuilder item(getSEGWindow(), str);
    item.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black });
    addComponent(item.build());
    refresh();
}

BoxBasic::item_ptr BoxBasic::popItem()
{
    auto item = backComponent<BoxItem>();
    popComponent();
    refresh();
    return item;
}

BoxBasic::item_ptr BoxBasic::removeItem(t_size idx)
{
    if (emptyComponent())
    {
        return nullptr;
    }

    setBoundedMenuIndex(INVALID_SIZE);
    auto it = removeComponentFromIndex(idx);
    refresh();

    if (emptyComponent())
    {
        return nullptr;
    }

    return dynamic_cast<item_ptr>(*it);
}

void BoxBasic::_autoFitBox(const t_size idx)
{
    if (countComponent() <= idx)
    {
        throw std::out_of_range{ "" };
        return;
    }
    if (atComponent(idx)->getControlTextWidth() > getWidth())
    {
        atComponent(idx)->setControlTextWidth(getWidth());
    }
}


bool BoxBasic::_isBoundInMenues()
{
    bool _isBoundInMenues = (getBoxStartIndex() <= getBoundedMenuIndex() && getBoundedMenuIndex() <= getBoxStartIndex() + getVisibleMenuCount());
    return  getBoundedMenuIndex() != INVALID_SIZE && _isBoundInMenues;
}

t_size BoxBasic::_calcIndexOf(const t_coord y)
{
    const size_t menuHeight = getMenuHeight() + MENU_GAP;

    int test_idx = (y - getPoint().y - menuHeight) / (menuHeight);
    if (test_idx >= getVisibleMenuCount())
    {
        return INVALID_SIZE;
    }

    if ((test_idx + getBoxStartIndex()) < countComponent()) {
        return test_idx + getBoxStartIndex();
    }

    return INVALID_SIZE;
}

//
// Created by chaed on 18. 12. 22.
//

#include "TControllBuilder.h"
#include "TGroupControllManager.h"

SDL_TETRIS

TControllBuilder::TControllBuilder(const TPoint& point, const std::string& str)
{
    m_basic.id = getId();
    m_basic.point = point;
    m_basic.name = str;
}

TControllBuilder::TControllBuilder(TPoint&& point, std::string&& str)
{
    m_basic.id = getId();
    m_basic.point = point;
    m_basic.name = str;
}


TControllBuilder* TControllBuilder::font(const TFont& font)
{
    m_basic.font = font;
    return this;
}

TControllBuilder* TControllBuilder::background_color(const TColorCode color)
{
    m_basic.background_color = color;
    return this;
}

TControllBuilder* TControllBuilder::width(const t_size size)
{
    m_basic.autoSize = false;
    m_basic.width = size;
    return this;

}

TControllBuilder* TControllBuilder::height(const t_size size)
{
    m_basic.autoSize = false;
    m_basic.height = size;
    return this;
}

TControllBuilder* TControllBuilder::enabled(const bool enable)
{
    m_basic.enabled = enable;
    return this;
}


TControllBuilder* TControllBuilder::display(const TDisplay display)
{
    m_basic.display = display;
    return this;
}

TControllBuilder* TControllBuilder::multiselected(const bool selected)
{
    m_basic.multiselected = selected;
    return this;
}

TControllBuilder* TControllBuilder::grouping(const size_t idx)
{
    m_basic.group = idx;
    return this;
}

TControllBuilder* TControllBuilder::carot()
{
    m_basic.carot = true;
    return this;
}

TControllBuilder* TControllBuilder::addCallback(const std::function<void(TOptionManager& mng, bool isSelected)>& fn)
{
    m_basic.callbackAry.emplace_back(fn);
    return this;
}

std::shared_ptr<TControllBasic> TControllBuilder::build() const
{
    if(m_basic.group != TGroupControllManager::NONE)
    {
        TGroupControllManager::getInstance()->add(m_basic.group, m_basic.id);
        if(m_basic.multiselected)
            TGroupControllManager::getInstance()->setMultiselect(m_basic.group);
    }

    auto basic = std::make_shared<TControllBasic>(m_basic);
    return basic;
}


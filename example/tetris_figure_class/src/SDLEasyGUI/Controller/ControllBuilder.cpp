//
// Created by chaed on 18. 12. 22.
//

#include "ControllBuilder.h"
#include "GroupControllManager.h"

SDL_TETRIS

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,const TPoint& point, const std::string& str)
    :m_window(window)
{
    m_basic.id = getId();
    m_basic.point = point;
    m_basic.name = str;
}

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,TPoint&& point, std::string&& str)
    :m_window(window)
{
    m_basic.id = getId();
    m_basic.point = point;
    m_basic.name = str;
}


ControllBuilder* ControllBuilder::font(const TFont& font)
{
    m_basic.font = font;
    return this;
}

ControllBuilder* ControllBuilder::background_color(const TColorCode color)
{
    m_basic.background_color = color;
    return this;
}

ControllBuilder* ControllBuilder::width(const t_size size)
{
    m_basic.autoSize = false;
    m_basic.width = size;
    return this;

}

ControllBuilder* ControllBuilder::height(const t_size size)
{
    m_basic.autoSize = false;
    m_basic.height = size;
    return this;
}

ControllBuilder* ControllBuilder::enabled(const bool enable)
{
    m_basic.enabled = enable;
    return this;
}


ControllBuilder* ControllBuilder::display(const TDisplay display)
{
    m_basic.display = display;
    return this;
}

ControllBuilder* ControllBuilder::multiselected(const bool selected)
{
    m_basic.multiselected = selected;
    return this;
}

ControllBuilder* ControllBuilder::grouping(const size_t idx)
{
    m_basic.group = idx;
    return this;
}

ControllBuilder* ControllBuilder::carot()
{
    m_basic.carot = true;
    return this;
}

ControllBuilder* ControllBuilder::selected()
{
    m_basic.selected = true;
    return this;
}

ControllBuilder* ControllBuilder::addCallback(const std::function<void(TOptionManager& mng, bool isSelected)>& fn)
{
    m_basic.callbackAry.emplace_back(fn);
    return this;
}

std::shared_ptr<TControllBasic> ControllBuilder::build() const
{
    if(m_basic.group != GroupControllManager::NONE)
    {
        GroupControllManager::getInstance()->add(m_basic.group, m_basic.id);
        if(m_basic.multiselected)
            GroupControllManager::getInstance()->setMultiselect(m_basic.group);
    }

    auto basic = std::make_shared<TControllBasic>(m_basic);
    return basic;
}


//
// Created by chaed on 18. 12. 22.
//

#include "ControllBuilder.h"
#include "GroupControllManager.h"

SDL_TETRIS

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,const TPoint& point, const std::string& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
}

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,TPoint&& point, std::string&& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
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


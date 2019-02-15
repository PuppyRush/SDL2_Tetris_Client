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

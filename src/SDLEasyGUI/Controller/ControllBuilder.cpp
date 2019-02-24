//
// Created by chaed on 18. 12. 22.
//

#include "ControllBuilder.h"
#include "GroupControllManager.h"

using namespace sdleasygui;
SDL_TETRIS

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,const Point& point, const std::string& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
}

ControllBuilder::ControllBuilder(const GraphicInterface::window_ptr window,Point&& point, std::string&& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
}

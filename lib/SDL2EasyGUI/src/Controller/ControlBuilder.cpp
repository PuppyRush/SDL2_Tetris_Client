//
// Created by chaed on 18. 12. 22.
//

#include "include/ControlBuilder.h"
#include "SDL2EasyGUI/include/GroupControlManager.h"

using namespace sdleasygui;

ControlBuilder::ControlBuilder(const GraphicInterface::window_type window, const SEG_Point& point,
                                     const std::string& str)
{
    m_basic.window = window;
    m_basic.point = point;
    m_basic.name = str;
}

ControlBuilder::ControlBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str)
{
    m_basic.window = window;
    m_basic.point = point;
    m_basic.name = str;
}

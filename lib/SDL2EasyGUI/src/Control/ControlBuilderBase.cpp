//
// Created by chaed on 18. 12. 22.
//

#include "include/ControlBuilderBase.h"
#include "SDL2EasyGUI/include/GroupControlManager.h"

using namespace seg;

ControlBuilderBase::ControlBuilderBase(const GraphicInterface::window_type window)
{
    m_basic.window = window;
}

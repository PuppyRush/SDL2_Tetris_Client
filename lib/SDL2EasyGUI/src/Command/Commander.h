//
// Created by chaed on 19. 2. 14.
//

#ifndef SDL2EASYGUI_COMMANDER_H
#define SDL2EASYGUI_COMMANDER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2EasyGUI/include/SEG_Type.h"

namespace seg {

class Commander
{

    virtual void execute() = 0;

};

}
#endif //SDL2EASYGUI_COMMANDER_H

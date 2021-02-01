//
// Created by chaed on 19. 2. 14.
//

#ifndef SDL2EASYGUI_EVENTCOMMAND_H
#define SDL2EASYGUI_EVENTCOMMAND_H

#if _MSC_VER >= 1200
#pragma once
#endif


#include "Commander.h"


namespace seg {

class EventCommand : public Commander
{

    virtual void execute() override final
    {

    }

};

}

#endif //SDL2EASYGUI_EVENTCOMMAND_H

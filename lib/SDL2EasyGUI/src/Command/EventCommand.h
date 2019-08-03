//
// Created by chaed on 19. 2. 14.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTCOMMAND_H
#define TETRIS_FIGURE_CLASS_EVENTCOMMAND_H

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

#endif //TETRIS_FIGURE_CLASS_EVENTCOMMAND_H

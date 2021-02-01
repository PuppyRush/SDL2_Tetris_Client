//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2EASYGUI_DECORATORINTERFACE_H
#define SDL2EASYGUI_DECORATORINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <unordered_map>

#include "../Control/Control.h"

namespace seg {

class DecoratorInterface : public Control
{
public:

    DecoratorInterface(Control* gi)
        : Control(gi)
    {

    }

    virtual ~DecoratorInterface()
    {
    }

    virtual void attach() = 0;

    virtual void detach() = 0;

private:

};

}

#endif //SDL2_TETRIS_CLIENT_DECORATOR_H

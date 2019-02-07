//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "DisplayController.h"
#include "Tetris/TDisplay/TMainLocalDisplay.h"
#include "Tetris/TDisplay/TMainOnlineDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "Tetris/TDisplay/TGameLocalDisplay.h"

SDL_TETRIS

DisplayController::DisplayController()
{
}

resource DisplayController::modal(display_ptr display)
{
    resource result;
    if(m_modalStack.empty())
    {
        m_modalStack.push(display);
    }
    else
    {
        display->run();

        auto parent = m_modalStack.top();
        SDL_SetWindowModalFor(display->getWindow()->getSDLWindow().get(),
            parent->getWindow()->getSDLWindow().get());
    }

    result = display->run();
    display.reset();

    return result;
}

void DisplayController::modaless(display_ptr display)
{
    DisplayInfo info{display->getDisplay(), display->getMode(), TDisplayMode::Modaless, display->getID()};
    if(m_modalessMap.count(info)==0)
    {
        m_modalessMap.insert(make_pair(info,display));
        display->run();
    }
    display->show();
}

void DisplayController::_release()
{
}


std::shared_ptr<DisplayController> DisplayController::getInstance()
{
    static auto inst = std::shared_ptr<DisplayController>(new DisplayController());
    return inst;
}
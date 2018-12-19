//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TDisplayController.h"
#include "../TMain/TMainLocalDisplay.h"
#include "../TMain/TMainOnlineDisplay.h"
#include "TGame/TGameLocalDisplay.h"

SDL_TETRIS

TDisplayController::TDisplayController()
{
    {
        auto dis = TMainLocalDisplay::getInstance();
        m_map.insert(make_pair(dis.get(), dis));
    }
    {
        auto dis = TLocalDisplayGame::getInstance();
        m_map.insert(make_pair(dis.get(), dis));
    }
}

static std::shared_ptr<TDisplayController> TDisplayController::getInstance()
{
    static auto inst = std::shared_ptr<TDisplayController>(new TDisplayController());
    return inst;
}
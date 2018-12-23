//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TDisplayController.h"
#include "TMain/TMainLocalDisplay.h"
#include "TMain/TMainOnlineDisplay.h"
#include "TOption/TOptionDisplay.h"
#include "TGame/TGameLocalDisplay.h"

SDL_TETRIS

TDisplayController::TDisplayController()
    :m_mode(TMode::Local)
{
    using namespace std;
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Main), TMainLocalDisplay::getInstance()));
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Game), TGameLocalDisplay::getInstance()));
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Option), TOptionDisplay::getInstance()));

    m_display = m_displayMap.at(make_pair(m_mode, m_currentDisplay));
}

void TDisplayController::operateGame()
{
    while(!m_programEnd)
    {
        m_display->show();
    }
}

std::shared_ptr<TDisplayController> TDisplayController::getInstance()
{
    static auto inst = std::shared_ptr<TDisplayController>(new TDisplayController());
    return inst;
}
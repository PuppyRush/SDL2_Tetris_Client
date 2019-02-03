//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "DisplayController.h"
#include "Tetris/TMain/TMainLocalDisplay.h"
#include "Tetris/TMain/TMainOnlineDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "TGameLocalDisplay.h"

SDL_TETRIS

DisplayController::DisplayController()
    :m_mode(TMode::Local),
    m_programEnd(false)
{
    using namespace std;
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Main), TMainLocalDisplay::getInstance()));
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Game), TGameLocalDisplay::getInstance()));
    m_displayMap.insert(make_pair( make_pair(TMode::Local, TDisplay::Option), TOptionDisplay::getInstance()));

    m_display = m_displayMap.at(make_pair(TMode::Local, TDisplay::Main));

}

void DisplayController::operateGame()
{
    while(!m_programEnd)
    {
        const auto key = std::make_pair(m_mode, m_currentDisplay);
        if(m_displayMap.count(key)>0)
            m_displayMap.at(key)->run();
        else
        {
            assert(0);
        }
    }

    _release();
}

void DisplayController::show()
{
    const auto key = std::make_pair(m_mode, m_currentDisplay);
    if(m_displayMap.count(key)>0)
        m_displayMap.at(key)->show();
    else
    {
        assert(0);
    }
}

void DisplayController::hidden()
{
    const auto key = std::make_pair(m_mode, m_currentDisplay);
    if(m_displayMap.count(key)>0)
        m_displayMap.at(key)->hidden();
    else
    {
        assert(0);
    }
}

void DisplayController::_release()
{
}


std::shared_ptr<DisplayController> DisplayController::getInstance()
{
    static auto inst = std::shared_ptr<DisplayController>(new DisplayController());
    return inst;
}
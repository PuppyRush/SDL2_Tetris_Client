//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>
#include <limits>

#include <SDL.h>
#include <SDL2/SDL.h>

#include "../SEG_Constant.h"
#include "DisplayController.h"
#include "Tetris/TDisplay/TMainLocalDisplay.h"
#include "Tetris/TDisplay/TMainOnlineDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "Tetris/TDisplay/TSingleGameDisplay.h"

SDL_TETRIS

DisplayController::DisplayController()
{
}

resource DisplayController::modal(display_ptr display)
{
    m_modalStack.emplace_back(display);

    display->initialize();

    resource result;
    if(!m_modalStack.empty())
    {
        auto parent = m_modalStack.front();
        SDL_SetWindowModalFor(display->getWindow()->getSDLWindow().get(),
            parent->getWindow()->getSDLWindow().get());
    }

    display->refresh();

    return result;
}

void DisplayController::modaless(display_ptr display)
{
    DisplayInfo info{display->getDisplay(), display->getMode(), TDisplayMode::Modaless, display->getID()};
    if( auto it = std::find_if(begin(m_modalessAry), end(m_modalessAry), [display](const display_ptr ptr)
    {
        return display->getID() == ptr->getID();
    }); it== m_modalessAry.end())
    {
        m_modalessAry.emplace_back(display);
    }
    display->initialize();
    display->refresh();


}

void DisplayController::close(const t_winid id)
{
    if(!m_modalStack.empty() && m_modalStack.back()->getWindowID() == id)
    {
        auto quitDisplay = m_modalStack.back();
        m_modalStack.pop_back();
    }
    else
    {
        std::remove_if(begin(m_modalessAry), end(m_modalessAry), [id](display_ptr display) {
            return display->getWindowID() == id;
        });
    }

}


void DisplayController::run()
{
    while(true)
    {

        auto sharedEvent = make_shared<SDL_Event>();
        auto event = sharedEvent.get();
        SDL_WaitEvent(event);

        const auto winid = getActivatedWindowID(event);
        if(winid != NULL_WINDOW_ID)
        {
            if(auto display = findFromId(winid)
                ; display != nullptr)
            {
                display->onEvent(event);
                //display->refresh();
            }
        }
        else
        {
            auto topDisplay = m_modalStack.back();
            topDisplay->onEvent(event);
           // topDisplay->refresh();

            for(const auto modaless : m_modalessAry) {
                modaless->onEvent(event);
                //modaless->refresh();
            }
        }

    }
}

DisplayController::display_ptr DisplayController::findFromId(const t_winid id)
{
    if( display_ptr display = _find(m_modalessAry, id);
        display != nullptr)
    {
        return display;
    } else{
        return _find(m_modalStack,id);
    }
}

t_winid DisplayController::getActivatedWindowID(const SDL_Event* event)
{
    t_winid windowId = NULL_WINDOW_ID;
    switch(event->type)
    {
        case SDL_USEREVENT:
            windowId = event->user.windowID;
            break;
        case SDL_WINDOWEVENT   :
            windowId = event->window.windowID;
            break;
        case SDL_SYSWMEVENT    :
            break;
        case SDL_KEYDOWN       :
        case SDL_KEYUP:
            windowId = event->key.windowID;
            break;
        case SDL_TEXTEDITING   :
        case SDL_TEXTINPUT:
            windowId = event->text.windowID;
            break;
        case SDL_KEYMAPCHANGED :
            break;
        case SDL_MOUSEMOTION   :
            windowId = event->motion.windowID;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP :
            windowId = event->button.windowID;
            break;
        case SDL_MOUSEWHEEL    :
            windowId = event->wheel.windowID;
            break;
        case SDL_JOYBUTTONDOWN   :
        case SDL_JOYBALLMOTION   :
        case SDL_JOYHATMOTION    :
        case SDL_JOYAXISMOTION   :
        case SDL_JOYBUTTONUP     :
        case SDL_JOYDEVICEADDED  :
        case SDL_JOYDEVICEREMOVED:
            break;
    }
    return windowId;
}


template <class T>
DisplayController::display_ptr DisplayController::_find(const T& ary, const t_winid id)
{
    auto it = std::find_if(begin(ary), end(ary), [id](const display_ptr ptr)
    {
      return id == ptr->getWindowID();
    });
    return it == ary.end() ? nullptr : *it;
}


void DisplayController::_release()
{
}


std::shared_ptr<DisplayController> DisplayController::getInstance()
{
    static auto inst = std::shared_ptr<DisplayController>(new DisplayController());
    return inst;
}
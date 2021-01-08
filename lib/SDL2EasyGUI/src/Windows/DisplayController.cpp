//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>
#include <limits>

#include <SDL2/SDL.h>

#include "include/SEG_Constant.h"
#include "include/SEG_Type.h"
#include "include/MessageDialog.h"
#include "include/DisplayController.h"

using namespace std;
using namespace seg;

DisplayController::DisplayController()
    :m_run(true)
{
}

DisplayController::~DisplayController()
{
    finish();
    m_thread.join();

}

void DisplayController::alert(display_type* display)
{
    m_alertAry.emplace_back(display);
    m_modalAryCV.notify_one();

}

void DisplayController::alert_close()
{
    assert(!m_alertAry.empty());
    m_alertAry.pop_back();
}

void DisplayController::modal_close(const display_ptr& dp)
{
    if (auto _dp = DisplayMap::getInstance().popModal(dp->getSuperWindowID()) ;
        _dp != nullptr)
    {
        //
    }
}


void DisplayController::modaless_close(display_type::unique_type uniqueId)
{
    if (auto dp = DisplayMap::getInstance().eraseModaless(uniqueId);
        dp != nullptr)
    {
        //
    }
}


void DisplayController::_preModalOpen(display_ptr display)
{

}

void DisplayController::_postOpenDisplay(display_ptr display)
{
    display->initialize();
    display->postCreate(display);
}

//void DisplayController::close(const display_ptr id)
//{
//    if
//    DisplayMap::getInstance().fi
//}

void DisplayController::run()
{
    m_mainDp->initialize();
    DisplayMap::getInstance().initialize(m_mainDp);
    m_mainDpThread = std::thread(&DisplayController::startMainDisplay, this);

    _pumpEvent();

    m_mainDpThread.join();
}

//�׸��� �̺�Ʈ�� �̰����� ó���ϰ� ������ �̺�Ʈ�� ��� �� dp�� push�Ѵ�.
void DisplayController::_pumpEvent()
{
    /*std::unique_lock<std::mutex> lock(m_modalAryMutex);
    m_modalAryCV.wait(lock, [=]() { return !m_modalStack.empty() || !m_modalessAry.empty(); });*/

     while (m_run) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        auto dp = DisplayMap::getInstance().find(event.window.windowID);
        if (dp == nullptr)
        {
            dp = DisplayMap::getInstance().find(event.user.windowID);
            if (dp == nullptr)
                continue;
        }

        if (event.type == SEG_DRAW ){
            dp->onEvent(event);
        }
        else {
            dp->pushEvent(event);
        }

        if (m_newDisplayQ.isEmpty() == false){
            auto dp = m_newDisplayQ.popEvent();
            _postOpenDisplay(dp);
        }
    }
}

template<class T>
DisplayController::display_ptr DisplayController::_find(const T& ary, const t_id id)
{
    auto it = std::find_if(begin(ary), end(ary), [id](const auto& ptr) {
        return id == ptr->getWindowID();
    });
    return it == ary.end() ? nullptr : *it;
}


t_id DisplayController::getActivatedWindowID(const SDL_Event* event)
{
    t_id windowId = NULL_WINDOW_ID;
    switch (event->type) {
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
        default:
            break;
    }
    return windowId;
}

void DisplayController::_release()
{
}

void DisplayController::finish()
{
    /*for (const auto display : m_modalStack) {
        event::
        event{display->getWindowID(), WINDOW_CLOSE};
        event.pushEvent();
    }

    for (auto& q : m_modalessAry)
    {
        for(const auto& dp : q)
        {
            event::EventPusher event {dp->getWindowID(), WINDOW_CLOSE};
            event.pushEvent();
        }
    }*/

    /* while(!m_modalStack.empty())
     {
         if(!(*m_modalStack.begin())->isRun())
         {
             delete m_modalStack.front();
             m_modalStack.pop_front();
         }
     }

     while(!m_modalessAry.empty())
     {
         if(!(*m_modalessAry.begin())->isRun())
         {
             auto dis = *m_modalessAry.begin();
             m_modalessAry.erase(m_modalessAry.begin());
             delete dis;
         }
     }*/

    m_run.exchange(false);
}

void DisplayController::refreshModal()
{
    //for (const auto display : m_modalStack) {
    //    display->refresh();
    //}
    //for (const auto display : m_modalessAry) {
    //    //display->refresh();
    //}
}

void DisplayController::getDisplay(const t_id displayId)
{

}

void DisplayController::setMainDisplay(const display_ptr dp)
{
    std::unique_lock<std::mutex> lock(m_mainDisplayChangeMutex);
    dp->setSuperWindowID(SUPER_WINDOWS_ID);
    m_mainDp = dp;
}

void DisplayController::startMainDisplay()
{
    m_mainDp->modaless();
}

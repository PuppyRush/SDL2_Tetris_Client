//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>
#include <limits>

#include <SDL2/SDL.h>

#include "SDL2EasyGUI/include/SEG_Constant.h"
#include "SDL2EasyGUI/include/SEG_Type.h"
#include "SDL2EasyGUI/include/MessageDialog.h"
#include "SDL2EasyGUI/include/DisplayController.h"

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



void DisplayController::modal_close()
{
    m_modalStack.pop_back();
}


void DisplayController::modaless_close(seg::t_id winid)
{
    for (const auto& q : m_modalessAry)
    {
        for (const auto& dp : q)
            if (winid == dp->getWindowID())
                ;//dp->postDestroy()
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

void DisplayController::close(const t_id id)
{
    if (!m_modalStack.empty() && m_modalStack.back()->getWindowID() == id) {
        auto quitDisplay = m_modalStack.back();
        m_modalStack.pop_back();
    } else {
        for (auto& q : m_modalessAry)
        {
            q.erase(std::remove_if(q.begin(), q.end(), [id](const auto& display) {
                return display->getWindowID() == id;
                }));
        }
    }
}

void DisplayController::run()
{
    m_mainDp->initialize();
    m_thread = std::thread(&DisplayController::_pumpEvent, this);
}

void DisplayController::_pumpEvent()
{
    /*std::unique_lock<std::mutex> lock(m_modalAryMutex);
    m_modalAryCV.wait(lock, [=]() { return !m_modalStack.empty() || !m_modalessAry.empty(); });*/

     while (m_run) {
        SDL_Event* event = new SDL_Event{};
        SDL_WaitEvent(event);

        auto dp = findFromId(event->window.windowID);
        if (dp == nullptr)
        {
            ;
        }

        dp->onEvent(*event);

        // printf("DisplayController::_pumpEvent : %d\n", debug++);

        //const auto winid = getActivatedWindowID(event);
        //if (winid != NULL_WINDOW_ID) {
        //    if (auto display = findFromId(winid); display != nullptr) {
        //        display->pushEvent(*event);
        //    }
        //} else {
        //    //broadcasting m_userEvent if not found something targeted id (display, controller)
        //    if (!m_modalStack.empty()) {
        //        m_modalStack.back()->pushEvent(*event);
        //    }

        //    for (auto& q : m_modalessAry)
        //    {
        //        for (const auto& dp : q)
        //        {
        //            dp->pushEvent(*event);
        //        }
        //    }
        //}

        //for (auto& display : m_alertAry) {
        //    display->pushEvent(*event);
        //}
    }
}

DisplayController::display_ptr DisplayController::findFromId(const t_id id)
{
    display_ptr dp = nullptr;
    for (const auto& q : m_modalessAry)
    {
        dp = _find(q, id);
        if (dp != nullptr)
            return dp;
    }

    return _find(m_modalStack, id);
}

template<class T>
DisplayController::display_ptr DisplayController::_find(const T ary, const t_id id)
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
    }
    return windowId;
}

void DisplayController::_release()
{
}

void DisplayController::finish()
{
    for (const auto display : m_modalStack) {
        event::EventPusher event{display->getWindowID(), WINDOW_CLOSE};
        event.pushEvent();
    }

    for (auto& q : m_modalessAry)
    {
        for(const auto& dp : q)
        {
            event::EventPusher event {dp->getWindowID(), WINDOW_CLOSE};
            event.pushEvent();
        }
    }

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
    for (const auto display : m_modalStack) {
        display->refresh();
    }
    for (const auto display : m_modalessAry) {
        //display->refresh();
    }
}

void DisplayController::getDisplay(const t_id displayId)
{

}

void DisplayController::setMainDisplay(const display_ptr dp)
{
    std::unique_lock<std::mutex> lock(m_mainDisplayChangeMutex);

    m_mainDp = dp;
}

void DisplayController::startMainDisplay()
{
    ////while (m_run)
    //{
    //    m_mainDp->modal();
    //}
    
}
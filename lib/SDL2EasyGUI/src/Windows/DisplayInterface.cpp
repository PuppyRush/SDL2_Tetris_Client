//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "magic_enum/include/magic_enum.hpp"
#include "SDL2EasyGUI/include/DisplayController.h"
#include "SDL2EasyGUI/include/SEG_Resource.h"
#include "SDL2EasyGUI/include/SEG_Event.h"

#include "include/DisplayInterface.h"

using namespace std;
using namespace sdleasygui;

DisplayInterface::DisplayInterface(const t_id displayId)
        : m_displayId(displayId)
{
    m_window = new SEG_Window;
}

DisplayInterface::~DisplayInterface()
{
    onClose();
}

void DisplayInterface::onInitialize()
{
    registerEvent();

}

void DisplayInterface::initialize()
{
    getWindow()->initialize();

    m_currentCtl = nullptr;
    setRun(true);

    onCreate();
    onInitialize();
    show();

   // return m_resultResrouce;
}

std::underlying_type_t<resource> DisplayInterface::alert()
{
    DisplayController::getInstance().alert(this);

    m_thread = thread(&DisplayInterface::_run, this);
    m_thread.join();

    DisplayController::getInstance().alert_close();

    return m_resultResrouce;

}

std::underlying_type_t<resource> DisplayInterface::modal(std::shared_ptr<DisplayInterface> display)
{
    modal_opener opener{display};

    m_thread = thread(&DisplayInterface::_run, this);
    m_thread.join();

    return m_resultResrouce;
}

void DisplayInterface::modaless(std::shared_ptr<DisplayInterface> display)
{
    DisplayController::getInstance().modaless_open(display);
    m_thread = thread(&DisplayInterface::_run, this);
}

std::underlying_type_t<resource> DisplayInterface::waitModaless()
{
    m_thread.join();
    return m_resultResrouce;
}

void DisplayInterface::_run()
{

    while (m_run) {
        auto event = m_eventDelivery.popEvent();
        onEvent(event);

        if (m_currentCtl != nullptr && (m_currentCtl->isBounded(*event) || m_currentCtl->isHitting())) {
            m_currentCtl->onEvent(event);
        }

        if (event->type >= sdleasygui::toUType(SEGEVENT_START)) {
            /*auto e = SEG_Event{event->type};
            printf("%s \n ", magic_enum::enum_name(e).value().data());*/
            //printf("recv seg event : %d\n", event->type);
        } else if (event->type == 0x8000) {
            // printf("recv user event : %d / %d \n", event->type, event->user.code);
        } else if (event->type == sdleasygui::toUType(SDL_TIMER_EVENT)) {
            //printf("recv timer event : %d / %d \n", event->type, event->user.code);
        } else {
            //printf("recv sdl event : %d\n", event->type);
        }

        //below event is deleted sdl
        if (event->type > 0x9999 || event->type < 0 || event->type == SDL_TIMER_EVENT) {
            continue;
        } else if (event->type == SDL_USEREVENT && (event->user.data1 || event->user.data2)) {
            delete static_cast<sdleasygui::t_eventType*>(event->user.data1);
        } else {
            delete event;
        }
    }
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event)
{
    switch (event->code) {
        case SEG_CLICKED_CONTROLLER: {
            t_res id = *static_cast<t_res*>(event->data1);
            SEG_Click* click = static_cast<SEG_Click*>(event->data2);
            _setResult(click->resourceId);

            if (m_callback_one_param.count(id) > 0) {
                m_callback_one_param.at(id)(click);
            }
            break;
        }
        case SEG_ENTER_CONTROLLER: {
            t_res id = *static_cast<t_res*>(event->data1);

            if (m_callback_one_param.count(id) > 0) {
                SDL_KeyboardEvent* keyevent = static_cast<SDL_KeyboardEvent*>(event->data2);
                m_callback_one_param.at(id)(keyevent);
            }
            break;
        }
        case SEG_DRAW_DISPLAY: {
            //dont call _refresh() in this case.
            onDrawBackground();
            onDraw();
            break;
        }
        case SEG_DRAW_CONTROLLER: {
            refresh();
            break;
        }
        case WINDOW_CLOSE:
            onClose();
            break;
        default:;
    }
}

void DisplayInterface::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    switch (key->keysym.sym) {
        case SDLK_RETURN:
            if (auto res = getCurrentControl();
                    res.first && res.second->isHitting()) {
                res.second->onHit(res.second->getMidPoint(), true);
            }
            break;
        case SDLK_ESCAPE:
            if (auto res = getCurrentControl();
                    res.first && res.second->isHitting()) {
                res.second->setHitting(false);
            }
            break;
    }
}

void DisplayInterface::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    menuHitTest(SEG_Point{button->x, button->y});
    refresh();
}

void DisplayInterface::onWindowEvent(const SDL_WindowEvent& window)
{
    switch (window.event) {
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_MOVED:
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESTORED:
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            refresh();
            break;
        case SDL_WINDOWEVENT_CLOSE:
            onDestroy();
            break;
    }
    //DisplayController::getInstance().refreshModal();
}

void DisplayInterface::onCreate()
{
    refresh();
}

void DisplayInterface::_release()
{
    auto renderer = getRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayInterface::onClose()
{
    if (m_resultResrouce == resource::NONE) {
        m_resultResrouce = resource::BTN_CLOSE;
    }

    setRun(false);
    hidden();

    onDestroy();
}

void DisplayInterface::onButtonClick(const void* event)
{
    const SEG_Click* click = static_cast<const SEG_Click*>(event);
    m_resultResrouce = click->resourceId;

    onClose();
}

void DisplayInterface::onOK()
{
    m_resultResrouce = BTN_OK;
    onClose();
}

void DisplayInterface::onNO()
{
    m_resultResrouce = BTN_NO;
    onClose();
}

void DisplayInterface::onCancel()
{
    m_resultResrouce = BTN_CANCEL;
    onClose();
}

void DisplayInterface::onDestroy()
{
    m_menus.clear();
}

void DisplayInterface::onDrawBackground()
{
    if (!m_backgroundImgPath.empty()) {
        auto renderer = getRenderer();

        t_size w, h; // m_texture width & height
        auto img = IMG_LoadTexture(renderer, m_backgroundImgPath.c_str());
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(renderer, img, NULL, &texr);
    } else {
        SDL_Rect rect = SDL_Rect{0, 0, getWindowWidth(), getWindowHeight()};
        GraphicInterface::_drawBackground(rect);
    }
}

void DisplayInterface::onDraw()
{
    _onDrawMenus();
    _release();
}

void DisplayInterface::_onDrawMenus()
{
    for (const auto& menu : m_menus) {
        menu->onVirtualDraw();
    }
}

void DisplayInterface::addControl(Control* newCtl)
{
    auto maybeCtl = dynamic_cast<Control*>(newCtl);
    if (maybeCtl == nullptr) {
        assert(0);
        return;
    }

    maybeCtl->initialize();

    auto it = std::find_if(begin(m_menus), end(m_menus), [newCtl](control_ptr exCtl) {
        return newCtl->getResourceId() == exCtl->getResourceId();
    });

    if (it != m_menus.end()) {
        assert(0);
        return;
    }

    m_menus.emplace_back(maybeCtl);
}


bool DisplayInterface::menuHitTest(const SEG_Point& point)
{
    for (const auto& menu : m_menus) {
        if (menu->isHit(point)) {
            m_currentCtl = menu;

            EventPusher event{this->getWindowID(), menu->getResourceId(), ATTACH_FOCUS};
            event.pushEvent();
            return true;
        } else {
            EventPusher event{this->getWindowID(), menu->getResourceId(), DETACH_FOCUS};
            event.pushEvent();
        }
    }
    return false;
}

void DisplayInterface::refresh()
{
    EventPusher event{this->getWindowID(), SEG_DRAW_DISPLAY};
    event.pushEvent();
}


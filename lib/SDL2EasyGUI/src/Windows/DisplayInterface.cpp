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

#include "GameInterface/include/Logger.h"

using namespace std;
using namespace seg;
using namespace game_interface;

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
	modal_opener opener{ display };

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
	initialize();

    //static int debug{0};

    while (m_run) {

		SDL_Event sdlEvent;
		SDL_WaitEvent(&sdlEvent);

        auto event = m_eventDelivery.popEvent();

        // printf("DisplayInterface::_run : %d\n", debug++);

        onEvent(&sdlEvent);

        if (m_currentCtl && m_currentCtl->isBounded(sdlEvent)) {
            m_currentCtl->onEvent(&sdlEvent);
        }

        if (m_currentCtl != nullptr && m_currentCtl->isHitting(sdlEvent) ) {
            m_currentCtl->onEvent(&sdlEvent);
        }

        if (sdlEvent.type >= seg::toUType(SEGEVENT_START)) {
            /*auto e = SEG_Event{event->type};
            printf("%s \n ", magic_enum::enum_name(e).value().data());*/
            //printf("recv seg event : %d\n", event->type);
        } else if (sdlEvent.type == 0x8000) {
            // printf("recv user event : %d / %d \n", event->type, event->user.code);
        } else if (sdlEvent.type == seg::toUType(SDL_TIMER_EVENT)) {
            //printf("recv timer event : %d / %d \n", event->type, event->user.code);
        } else {
            //printf("recv sdl event : %d\n", event->type);
        }

        //below event is deleted sdl
        if (sdlEvent.type > 0x9999 || sdlEvent.type < 0 || sdlEvent.type == SDL_TIMER_EVENT) {
            continue;
        } 
		/*else if (event->type == SDL_USEREVENT && (event->user.data1 || event->user.data2)) {
            delete static_cast<seg::t_eventType*>(event->user.data1);
        } else {
            delete event;
        }*/

    }
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event)
{
    switch (event->code) {
        case SEG_CLICKED_CONTROLLER: {
            t_id id = *static_cast<t_id*>(event->data1);
            event::SEG_Click* click = static_cast<event::SEG_Click*>(event->data2);
            _setResult(click->resourceId);

            if (m_callback_one_param.count(id) > 0) {
                m_callback_one_param.at(id)(click);
            }
            break;
        }
        case SEG_ENTER_CONTROLLER: {
            t_id id = *static_cast<t_id*>(event->data1);

            if (m_callback_one_param.count(id) > 0) {
                SDL_KeyboardEvent* keyevent = static_cast<SDL_KeyboardEvent*>(event->data2);
                m_callback_one_param.at(id)(keyevent);
            }
            break;
        }
        case SEG_DRAW_CONTROLLER:
        case SEG_DRAW_DISPLAY: {
            //dont call _refresh() in this case.
            onDrawBackground();
            onDraw();
            break;
        }
        case WINDOW_CLOSE:
            onClose();
            break;
        case SEG_DECORATOR_ATTACH: {
            t_id id = *static_cast<t_id*>(event->data1);
            control_ptr decorator = static_cast<control_ptr>(event->data2);

            if (auto ctl = getControl(id); ctl != nullptr) {
                attachDecorator(ctl, decorator);
            } else {
                assert(0);
            }
            break;
        }
        case SEG_DECORATOR_DETACH: {
            t_id id = *static_cast<t_id*>(event->data1);
            auto origin = static_cast<Control*>(event->data2);
            if (auto deco = getControl(id); deco != nullptr && origin->getId() == deco->getId()) {
                detachDecorator(origin);
            } else {
                assert(0);
            }
            break;
        }
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
    const event::SEG_Click* click = static_cast<const event::SEG_Click*>(event);
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
    getMenuAry().clear();
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
   logger::Logger::getInstance().printLog("DisplayInterface::onDraw()",
                                           logger::Logger::logger_level::Debug);

    _onDrawMenus();
    _release();
}

void DisplayInterface::_onDrawMenus()
{
    for (const auto& menu : getMenuAry()) {
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

    auto it = std::find_if(begin(getMenuAry()), end(getMenuAry()), [newCtl](control_ptr exCtl) {
        return newCtl->getId() == exCtl->getId();
    });

    if (it != getMenuAry().end()) {
        assert(0);
        return;
    }

    getMenuAry().emplace_back(maybeCtl);
}

bool DisplayInterface::removeControl(control_ptr ctl)
{

    if (auto dest = findControl(ctl->getId()); dest != getMenuAry().end()) {
        getMenuAry().erase(dest);
        return true;
    }

    return false;
}

void DisplayInterface::menuHitTest(const SEG_Point& point)
{
    if (m_currentCtl && m_currentCtl->isHit(point)) {
        return;
    }

    for (const auto& menu : getMenuAry()) {
        if (menu->isHit(point)) {
            m_currentCtl = menu;

            event::EventPusher event{this->getWindowID(), menu->getId(), ATTACH_FOCUS};
            event.pushEvent();
            break;
        }
    }
}

void DisplayInterface::refresh()
{
    event::EventPusher event{this->getWindowID(), SEG_DRAW_DISPLAY};
    event.pushEvent();
}

void DisplayInterface::attachDecorator(const control_ptr ctl, control_ptr decorator)
{
    if (removeControl(ctl)) {
        addControl(decorator);
        m_currentCtl = decorator;
    }

}

void DisplayInterface::detachDecorator(const control_ptr ctl)
{
    if (removeControl(ctl)) {
        addControl(ctl);
        m_currentCtl = ctl;
    }
}

DisplayInterface::control_ptr
DisplayInterface::getControl(const t_id resourceId)
{
    return *find_if(begin(getMenuAry()), end(getMenuAry()), [resourceId](control_ptr ptr) {
        return ptr->getId() == resourceId;
    });
}

DisplayInterface::control_ary_it
DisplayInterface::findControl(const t_id resourceId)
{
    return find_if(begin(getMenuAry()), end(getMenuAry()), [resourceId](control_ptr ptr) {
        return ptr->getId() == resourceId;
    });
}
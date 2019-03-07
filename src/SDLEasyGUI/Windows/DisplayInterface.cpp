//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "GameInterface/Online/PacketQueue.h"
#include "GameInterface/Object/Atomic.h"
#include "DisplayController.h"
#include "DisplayInterface.h"
#include "../SEG_Resource.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;
using namespace sdleasygui;

DisplayInterface::DisplayInterface()
    :m_currentCtl(nullptr)
{
}


DisplayInterface::~DisplayInterface()
{
    onClose();
}

void DisplayInterface::onPreInitialize()
{
    registerEvent();
}

t_res DisplayInterface::initialize()
{
    onCreate();
    onPreInitialize();
    show();

}

std::underlying_type_t<resource> DisplayInterface::modal()
{
    modal_opener opener{this};

    promise<resource> pm;
    auto f = pm.get_future();

    m_thread = thread(&DisplayInterface::_run, this, std::move(pm) );
    m_thread.join();

    return toUType(f.get());
}

void DisplayInterface::modaless()
{
    promise<resource> pm;
    auto f = pm.get_future();

    DisplayController::getInstance()->modaless(this);

    m_thread = thread(&DisplayInterface::_run, this, std::move(pm));
    f.get();
}

void DisplayInterface::_run(std::promise<resource> &&pm){

    while(m_run)
    {
        const event_mover e = popEvent();
        onEvent(e.event);

        if( m_currentCtl )
        {
            m_currentCtl->onEvent(e.event);
        }
    }

    pm.set_value(m_modalresult);
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event) {
    switch (event->code) {
        case SEG_CLICKED_CONTROLLER:
        {
            t_res id = *static_cast<t_res*>(event->data1);
            if(m_callback_no_param.count(id)>0)
                m_callback_no_param.at(id)();
            break;
        }
        case SEG_DRAW_DISPLAY:
            //dont call _refresh() in this case.
            onDraw();
            onDrawMenus();
            release();
            break;
        case SEG_DRAW_CONTROLLER:
        {
            refresh();
            /*const auto it = std::find_if(begin(m_items), end(m_items), [event](const Controll::controll_ptr ctl) {
              return ctl->getResourceId() == *static_cast<game_interface::t_id*>(event->data1);
            });
            if(it != m_items.end())
            {
                (*it)->onVirtualDraw();
            }
            release();*/
            break;
        }
        case WINDOW_CLOSE:
            onClose();
            break;
        default:;
    }
}

void DisplayInterface::onMouseButtonEvent (const SDL_MouseButtonEvent* button)
{
    clickedMenuEvent(TPoint{button->x, button->y});
    refresh();
}

void DisplayInterface::onMouseMotionEvent(const SDL_MouseMotionEvent *motion)
{
}


void DisplayInterface::onWindowEvent (const SDL_WindowEvent& window)
{
    switch(window.type)
    {
//      case SDL_QUIT:
//            setRun(false);
//            break;
        case SDL_WINDOWEVENT_MOVED:
        case SDL_WINDOWEVENT_CLOSE:
            onDestroy();
            break;
    }
    DisplayController::getInstance()->refreshModal();
}

void DisplayInterface::onCreate()
{
    auto window = make_shared<Window>();
    setWindow(window);
    refresh();
}

void DisplayInterface::release()
{
    auto renderer = getRenderer().get();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayInterface::onClose()
{
    if(m_modalresult == resource::NONE)
        m_modalresult = resource::BTN_CLOSE;

    setRun(false);
    hidden();
    onDestroy();

}

void DisplayInterface::onOK()
{
    m_modalresult = BTN_OK;
    onClose();
}

void DisplayInterface::onNO(){
    m_modalresult = BTN_NO;
    onClose();
}

void DisplayInterface::onCancel()
{
    m_modalresult = BTN_CANCEL;
    onClose();
}

void DisplayInterface::onDestroy()
{
    SDL_DestroyRenderer(getRenderer().get());
    SDL_DestroyWindow(getSDLWindow().get());

}

void DisplayInterface::onDraw()
{
    onDrawMenus();
}

void DisplayInterface::onDrawMenus()
{
    for(const auto& menu : m_menus)
    {
        menu->onVirtualDraw();
    }
}

void DisplayInterface::addControll(const shared_ptr<Controll> ctl)
{
    ctl->initialize();
    m_menus.emplace_back(ctl);

}

bool DisplayInterface::clickedMenuEvent(const TPoint& point)
{
    for(const auto& menu : m_menus)
    {
        if(menu->isHit(point))
        {
            m_currentCtl = menu.get();

            EventPusher event{this->getWindowID(), menu->getResourceId(), ATTACH_FOCUS };
            event.pushEvent();
            return true;
        }
        else
        {
            EventPusher event{this->getWindowID(), menu->getResourceId(), DETACH_FOCUS };
            event.pushEvent();
        }
    }
    return false;
}

void DisplayInterface::refresh()
{
    EventPusher event{this->getWindowID(), SEG_DRAW_DISPLAY };
    event.pushEvent();
}

void DisplayInterface::event_buttonClick(const t_res id, const BTN_CLICK callback_fn)
{
    m_callback_no_param.insert(make_pair(id,callback_fn));
}


bool  DisplayInterface::validId(const game_interface::t_id id) noexcept
{
    return getWindowID() == id;
}
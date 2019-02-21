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

DisplayInterface::DisplayInterface()
    :m_id(Atomic::newUnique()), m_currentCtl(nullptr)
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

void DisplayInterface::onPreDraw()
{


   /* if(!m_backgroundImgPath.empty())
    {
        auto renderer = getRenderer().get();

        t_size w, h; // texture width & height
        auto img = IMG_LoadTexture(renderer, m_backgroundImgPath.c_str());
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(renderer, img, NULL, &texr);
    }*/
}

t_res DisplayInterface::initialize()
{
    onCreate();
    onPreInitialize();
    show();

}

t_res DisplayInterface::modal()
{
    modal_opener opener{this};
    PacketQueue::getInstance().attach(this);

    m_thread = thread(&DisplayInterface::_run, this);
    m_thread.join();
}

void DisplayInterface::modaless()
{
    PacketQueue::getInstance().attach(this);
    DisplayController::getInstance()->modaless(this);

    m_thread = thread(&DisplayInterface::_run, this);
}

void DisplayInterface::_run(){

    while(m_run)
    {
        const event_mover e = popEvent();
        onEvent(e.event);

        if( m_currentCtl )
        {
            m_currentCtl->onEvent(e.event);
        }
    }
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event) {
    switch (event->type) {
        case SDL_CLICKED_CONTROLLER:
        {
            auto id = static_cast<t_res>(event->code);
            if(m_callback_no_param.count(id)>0)
                m_callback_no_param.at(id)();
        }
            break;
        case SDL_DRAW_DISPLAY:
            //dont call _refresh() in this case.
            onDraw();
            onDrawMenus();
            release();
            break;
        case SDL_DRAW_CONTROLLER: {
            const auto it = std::find_if(begin(m_menus), end(m_menus), [event](const Controll::controll_ptr ctl) {
              return ctl->getId() == static_cast<game_interface::t_id>(event->code);
            });
            {
                m_currentCtl->onVirtualDraw();
            }
            break;
        }
        default:;
    }
}

void DisplayInterface::onMouseButtonEvent (const SDL_MouseButtonEvent* button)
{
    clickedMenuEvent(Point{button->x, button->y});
    refresh();
}


void DisplayInterface::onWindowEvent (const SDL_WindowEvent& window)
{
    switch(window.type)
    {
//      case SDL_QUIT:
//            setRun(false);
//            break;
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
    onTimer();
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
    setRun(false);
    hidden();
    onDestroy();
}

void DisplayInterface::onOK()
{

    onClose();
}

void DisplayInterface::onNO(){
    onClose();
}

void DisplayInterface::onCancel()
{
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

/*
template <class T>
Controll::controll_ptr DisplayInterface::getControll(const T res)
{
    return *find_if(begin(m_menus), end(m_menus),[res](Controll::controll_ptr ptr)
    {
        if(ptr->getId() == toUType(res))
            return true;
        return false;
    });
}
*/

bool DisplayInterface::clickedMenuEvent(const Point& point)
{
    for(const auto& menu : m_menus)
    {
        if(menu->isHit(point))
        {
            m_currentCtl = menu.get();

            SDL_UserEvent userevent;
            userevent.type = ATTACH_FOCUS  ;
            userevent.code = menu->getId();
            userevent.windowID = this->getWindowID();

            SDL_Event event;
            event.type = SDL_USEREVENT;
            event.user = userevent;

            SDL_PushEvent(&event);

            return true;
        }
        else
        {
            SDL_UserEvent userevent;
            userevent.type = DETACH_FOCUS  ;
            userevent.code = menu->getId();
            userevent.windowID = this->getWindowID();

            SDL_Event event;
            event.type = SDL_USEREVENT;
            event.user = userevent;

            SDL_PushEvent(&event);
        }
    }
    return false;
}

void DisplayInterface::refresh()
{
    SDL_UserEvent userevent;
    userevent.type = SDL_DRAW_DISPLAY  ;
    userevent.code = 0;
    userevent.windowID = this->getWindowID();

    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
}

void DisplayInterface::event_buttonClick(const t_res id, const BTN_CLICK callback_fn)
{
    m_callback_no_param.insert(make_pair(id,callback_fn));
}


bool  DisplayInterface::validId(const game_interface::t_id id)
{
    return getWindowID() == id;
}
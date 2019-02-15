//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "GameInterface/Object/Atomic.h"
#include "DisplayController.h"
#include "DisplayInterface.h"
#include "../SEG_Resource.h"

SDL_TETRIS

DisplayInterface::DisplayInterface()
    :m_id(Atomic::newUnique())
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

    m_thread = std::thread(&DisplayInterface::_run, this);
    m_thread.join();
}

void DisplayInterface::modaless()
{
    DisplayController::getInstance()->modaless(this);
    m_thread = std::thread(&DisplayInterface::_run, this);
}

void DisplayInterface::_run(){

    while(m_run)
    {
        const event_mover e = popEvent();
        onEvent(e.event);
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
            _release();
            break;
        default:;
    }
}

void DisplayInterface::onMouseButtonEvent (const SDL_MouseButtonEvent* button)
{
    clickedMenuEvent(TPoint{button->x, button->y});
    pushDrawDisplayEvent();
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
    pushDrawDisplayEvent();
}

void DisplayInterface::_release()
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
        menu->onDraw();
    }
}

void DisplayInterface::addControll(const std::shared_ptr<Controll> ctl)
{
    ctl->initialize();
    m_menus.emplace_back(ctl);
}

Controll::controll_ptr DisplayInterface::getControll(const t_res res)
{
    return *std::find_if(begin(m_menus), end(m_menus),[res](Controll::controll_ptr ptr)
    {
        if(ptr->getId() == res)
            return true;
        return false;
    });
}

bool DisplayInterface::clickedMenuEvent(const TPoint& point)
{
    for(const auto& menu : m_menus)
    {
        if(menu->isHit(point))
        {
            return true;
        }

    }
    return false;
}

void DisplayInterface::pushDrawDisplayEvent()
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

bool  DisplayInterface::validId(const t_id id)
{
    return getWindowID() == id;
}
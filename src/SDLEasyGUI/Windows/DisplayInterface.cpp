//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "GameInterface/Object/Atomic.h"
#include "DisplayController.h"
#include "DisplayInterface.h"

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

void DisplayInterface::_initializing()
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

resource DisplayInterface::run()
{
    onCreate();
    onPreInitialize();
    show();

    auto _e = getSDLEvent().get();

    while(m_run)
    {
        _initializing();

        SDL_WaitEvent(_e);
        event(_e);

    }

    onClose();
    onDestroy();
}


void DisplayInterface::event(const SDL_Event *event)
{
    switch (event->type) {
        case SDL_WINDOWEVENT:
            onWindowEvent(event);
            refresh();
            break;
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_MOUSEBUTTONDOWN:
            clickedMenuEvent(TPoint{event->button.x, event->button.y});
            refresh();
            break;
        case SDL_CLICKED_CONTROLLER:
        {
            auto id = static_cast<resource>(event->user.code);
            if(m_callback_no_param.count(id)>0)
                m_callback_no_param.at(id)();
        }
            break;
        case SDL_DRAW_DISPLAY:
            //dont call _refresh() in this case.
            onDraw();
            _onDrawMenus();
            _release();
            break;
        default:;
    }
}

void DisplayInterface::onWindowEvent(const SDL_Event *event)
{
    switch(event->window.type)
    {
        case SDL_WINDOWEVENT_CLOSE:
            onDestroy();
            break;
    }

}

void DisplayInterface::onCreate()
{
    auto window = make_shared<Window>();
    setWindow(window);

    timer();
    refresh();
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
    setRun(true);
    hidden();
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
    SDL_Quit();
}

void DisplayInterface::_onDrawMenus()
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

Controll::controll_ptr DisplayInterface::getControll(const resource res)
{
    return *std::find_if(begin(m_menus), end(m_menus),[res](Controll::controll_ptr ptr)
    {
        if(ptr->getId() == toUType(res))
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

void DisplayInterface::refresh()
{
    SDL_UserEvent userevent;
    userevent.type = SDL_DRAW_DISPLAY  ;
    userevent.code = 0;

    SDL_Event event;
    event.type = SDL_DRAW_DISPLAY;
    event.user = userevent;

    SDL_PushEvent(&event);
}


void DisplayInterface::event_buttonClick(const resource id, const BTN_CLICK callback_fn)
{
    m_callback_no_param.insert(make_pair(id,callback_fn));
}
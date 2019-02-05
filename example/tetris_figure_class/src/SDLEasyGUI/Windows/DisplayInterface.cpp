//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>

#include "DisplayController.h"
#include "DisplayInterface.h"

SDL_TETRIS

DisplayInterface::DisplayInterface()
     :m_goBack(true)
{
}


DisplayInterface::~DisplayInterface()
{
    onClose();

}

void DisplayInterface::onPreInitialize()
{

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

void DisplayInterface::run()
{
    onCreate();
    onPreInitialize();
    show();

    while(m_run)
    {
        _initializing();

        SDL_WaitEvent(getSDLEvent().get());
        _event(getSDLEvent().get());
    }

    onClose();
    onDestroy();
}


void DisplayInterface::_event(const SDL_Event* event)
{
    switch (event->type) {
        case SDL_WINDOWEVENT:
            onWindowEvent(event);
            break;
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_DRAWDISPLAY:
            //dont call _refresh() in this case.
            onDraw();
            _onDrawMenus();
            _release();
            break;
        case SDL_MOUSEBUTTONDOWN: {
            clickedMenuEvent(TPoint{event->button.x, event->button.y});
            break;
        }
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
    _refresh();
}

void DisplayInterface::onCreate()
{
    auto window = make_shared<Window>();
    setWindow(window);

    _timer();
    _refresh();
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

bool DisplayInterface::clickedMenuEvent(const TPoint& point)
{
    for(const auto& menu : m_menus)
    {
        if(menu->isHit(point))
        {
            switch(menu->getDisplay())
            {
                case TDisplay::None:
                    break;
                case TDisplay::Exit:
                    DisplayController::getInstance()->setProgramEnd(true);
                    break;
                default:
                    setRun(false);
            }

            setDisplay(menu->getDisplay());
            return true;
        }

        /*for( auto callback : menu->getCallbackAry())
        {
            callback(*TOptionManager::getInstance().get(), isSelected);
        }*/

    }
    return false;
}

void DisplayInterface::setDisplay(const TDisplay dp)
{
    DisplayController::getInstance()->setDisplay(dp);
    m_display = dp;
}


void DisplayInterface::_refresh()
{
    SDL_UserEvent userevent;
    userevent.type = SDL_DRAWDISPLAY;
    userevent.code = 0;

    SDL_Event event;
    event.type = SDL_DRAWDISPLAY;
    event.user = userevent;

    SDL_PushEvent(&event);
}

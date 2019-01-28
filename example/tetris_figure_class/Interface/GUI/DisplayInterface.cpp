//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>

#include "DisplayController.h"
#include "DisplayInterface.h"

SDL_TETRIS

DisplayInterface::DisplayInterface()
     :m_goBack(true),
//     m_canGoOtherDisplay(true),
     m_window(make_shared<Window>())
{
}


DisplayInterface::~DisplayInterface()
{
    SDL_DestroyRenderer(getRenderer().get());
    SDL_DestroyWindow(getSDLWindow().get());
    SDL_Quit();
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
    _preInitialize();
    _timer();
    _refresh();
    show();

    while(m_run)
    {
        _initializing();

        SDL_WaitEvent(getSDLEvent().get());
        _event(getSDLEvent().get());
    }

    setRun(true);
    hidden();
}


void DisplayInterface::_event(const SDL_Event* event)
{
    switch (event->type) {
        case SDL_WINDOWEVENT:
            _refresh();
            break;
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_DRAWDISPLAY:
            _draw();
            _drawMenus();
            _release();
            break;
        case SDL_MOUSEBUTTONDOWN: {
            const TPoint point(event->button.x, event->button.y);
            if (clickedMenuEvent(point))
            {
                break;
            }
            _refresh();
            break;
        }
        default:;
    }
}

void DisplayInterface::_drawMenus()
{
    for(const auto& menu : m_menus)
    {
        menu->draw();
    }
}

void DisplayInterface::_release()
{
    auto renderer = getRenderer().get();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayInterface::addMenu(const std::shared_ptr<Controll> ctl)
{
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

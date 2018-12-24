//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>

#include "TDisplayInterface.h"

SDL_TETRIS

TDisplayInterface::TDisplayInterface()
     :m_goBack(true),
     m_canGoOtherDisplay(true),
     m_window(TWindow::getInstance())
{
}


TDisplayInterface::~TDisplayInterface()
{
    SDL_DestroyRenderer(getRenderer().get());
    SDL_DestroyWindow(getWindow().get());
    SDL_Quit();
}

void TDisplayInterface::_initialize() {

    if(!m_backgroundImgPath.empty())
    {
        auto renderer = getRenderer().get();

        int w, h; // texture width & height
        auto img = IMG_LoadTexture(renderer, "resources/background.jpg");
        SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
        // put the location where we want the texture to be drawn into a rectangle
        // I'm also scaling the texture 2x simply by setting the width and height
        SDL_Rect texr;
        texr.x = -50;
        texr.y = 100;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(renderer, img, NULL, &texr);
    }
}

void TDisplayInterface::show()
{

    _initialize();
    _timer();

    while(m_run)
    {
        _draw();

        SDL_WaitEvent(getSDLEvent().get());
        _event(getSDLEvent().get());
        _release();
    }
}

void TDisplayInterface::_release()
{
    auto renderer = getRenderer().get();
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}


void TDisplayInterface::hide()
{

}


void TDisplayInterface::erase()
{

}

void TDisplayInterface::addMenu(const TMenuBuilder& bld)
{
    const auto& ary = bld.getMenus();
    for(const auto& menu : ary)
    {
        this->m_menus.emplace_back(menu);
    }
}

bool TDisplayInterface::clickedMenuEvent(const TPoint& point)
{
    if(!m_canGoOtherDisplay)
        return false;

    for(const auto& menu : m_menus)
    {
        if(menu->display == TDisplay::None)
            continue;

        //check hit
        if ((menu->point.x <= point.x && point.x <= menu->point.x + menu->width)
            && (menu->point.y <= point.y && point.y <= menu->point.y + menu->height))
        {
            setDisplay(menu->display);
            return true;
        }
    }
    return false;
}
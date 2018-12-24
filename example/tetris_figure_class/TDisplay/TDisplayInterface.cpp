//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>

#include "TDisplayController.h"
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

        t_size w, h; // texture width & height
        auto img = IMG_LoadTexture(renderer, m_backgroundImgPath.c_str());
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        SDL_Rect texr;
        texr.x = 0;
        texr.y = 0;
        texr.w = w;
        texr.h = h;
        SDL_RenderCopy(renderer, img, NULL, &texr);
    }
}

void TDisplayInterface::show()
{
    _timer();

    while(m_run)
    {
        _initialize();

        _draw();

        SDL_WaitEvent(getSDLEvent().get());
        _event(getSDLEvent().get());

        _drawMenus();
        _release();
    }
    setRun(true);
}

void TDisplayInterface::_drawMenus()
{
    auto renderer = getRenderer().get();

    for(const auto& menu : m_menus)
    {
        SDL_Rect rect;
        rect.y = menu->point.y;
        rect.x = menu->point.x;
        rect.h = menu->height;
        rect.w = menu->width;

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderDrawRect(renderer, &rect);


        TTF_Font* font = TTF_OpenFont("../resources/fonts/OpenSans-Bold.ttf", 24);
        std::string score_text = menu->name;
        SDL_Color textColor = { 255, 255, 255, 0 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
        SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);

        int text_width = textSurface->w;
        int text_height = textSurface->h;
        SDL_FreeSurface(textSurface);

        t_coord font_x  = menu->point.x + ( menu->width - text_width)/2;
        t_coord font_y  = menu->point.y + ( menu->height - text_height)/2;

        SDL_Rect renderQuad = { font_x, font_y , text_width, text_height };
        SDL_RenderCopy(renderer, text, NULL, &renderQuad);
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
            if(menu->display == TDisplay::Exit)
                TDisplayController::getInstance()->setProgramEnd(true);

            setDisplay(menu->display);
            return true;
        }
    }
    return false;
}

void TDisplayInterface::setDisplay(const TDisplay dp)
{
    TDisplayController::getInstance()->setDisplay(dp);
    m_display = dp;
}
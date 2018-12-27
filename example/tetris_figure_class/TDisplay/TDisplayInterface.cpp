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

void TDisplayInterface::_initializing() {

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
    _preInitialize();
    _timer();

    while(m_run)
    {
        _initializing();

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
        SDL_Rect rect{ menu->getPoint().x, menu->getPoint().y, menu->getWidth(), menu->getHeight()};

        const auto& back_color = menu->getBackground_color();
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);
        SDL_RenderDrawRect(renderer, &rect);

        const auto& fontinfo = menu->getFont();
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        std::string score_text = menu->getName();
        SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
        SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);

        int text_width = textSurface->w;
        int text_height = textSurface->h;
        SDL_FreeSurface(textSurface);

        t_coord font_x  = menu->getPoint().x + ( menu->getWidth() - text_width)/2;
        t_coord font_y  = menu->getPoint().y + ( menu->getHeight() - text_height)/2;

        SDL_Rect renderQuad = { font_x, font_y , text_width, text_height };
        SDL_RenderCopy(renderer, text, NULL, &renderQuad);

    }
    m_drawMenus = false;
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

void TDisplayInterface::addMenu(const std::shared_ptr<TControll> ctl)
{
    m_menus.emplace_back(ctl);
}

bool TDisplayInterface::clickedMenuEvent(const TPoint& point)
{
    if(!m_canGoOtherDisplay)
        return false;

    for(const auto& menu : m_menus)
    {
        if(menu->getDisplay() == TDisplay::None)
            continue;

        const auto menu_x = menu->getPoint().x;
        const auto menu_y = menu->getPoint().y;

        //check hit
        if ((menu_x <= point.x && point.x <= menu_x + menu->getWidth())
            && (menu_y <= point.y && point.y <= menu_y + menu->getHeight()))
        {
            if(menu->getDisplay() == TDisplay::Exit)
                TDisplayController::getInstance()->setProgramEnd(true);

            setDisplay(menu->getDisplay());
            //menu->setClicked(true);
            return true;
        }
       /* else
            menu->setClicked(false);*/
    }
    return false;
}

void TDisplayInterface::setDisplay(const TDisplay dp)
{
    TDisplayController::getInstance()->setDisplay(dp);
    m_display = dp;
}
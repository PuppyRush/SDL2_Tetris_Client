//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>

#include "TDisplayInterface.h"

SDL_TETRIS

TDisplayInterface::TDisplayInterface()
    :m_windowHeight(tetris::DISPLAY_HEIGHT),
     m_windowWidth(tetris::DISPLAY_WIDTH),
     m_event( std::make_shared<SDL_Event>()),
     m_goBack(true)
{
    using namespace std;

    try
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            string s("SDL_Init error: " );
            s.append(SDL_GetError());
            throw runtime_error(s);
        }

        auto window_deleter = [](SDL_Window* window) {
          if(window==nullptr) delete window;
        };

        m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("SDL_TETRIS",
                                                                SDL_WINDOWPOS_UNDEFINED,
                                                                SDL_WINDOWPOS_UNDEFINED,
                                                                m_windowWidth,
                                                                m_windowHeight,
                                                                SDL_WINDOW_SHOWN), window_deleter);

        auto renderer_deleter = [](SDL_Renderer* window) {
          if(window==nullptr) delete window;
        };

        m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(),
                                                                      -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
            , renderer_deleter);


    }
    catch(runtime_error &e)
    {
        std::cerr << e.what();
    }
    catch(...)
    {
        std::cerr << "fail tetris game init because of unkwon error ";
    }

}


TDisplayInterface::~TDisplayInterface()
{
    SDL_DestroyRenderer(getRenderer().get());
    SDL_DestroyWindow(getWindow().get());
    SDL_Quit();
}

void TDisplayInterface::show()
{
    _setDisplay();
}

void TDisplayInterface::hide()
{

}

void TDisplayInterface::draw()
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

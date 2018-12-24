//
// Created by chaed on 18. 12. 24.
//

#include <iostream>

#include "TWindow.h"

SDL_TETRIS

TWindow::TWindow()
    :m_windowHeight(tetris::DISPLAY_HEIGHT),
     m_windowWidth(tetris::DISPLAY_WIDTH),
     m_event( std::make_shared<SDL_Event>())
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

std::shared_ptr<TWindow> TWindow::getInstance()
{
    static std::shared_ptr<TWindow > inst = std::shared_ptr<TWindow>(new TWindow());
    return inst;


}


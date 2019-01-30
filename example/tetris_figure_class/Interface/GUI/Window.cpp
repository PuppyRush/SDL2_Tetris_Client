//
// Created by chaed on 18. 12. 24.
//

#include <iostream>

#include "Window.h"

SDL_TETRIS

Window::Window()
    :m_windowHeight(tetris::WINDOW_HEIGHT),
     m_windowWidth(tetris::WINDOW_WIDTH),
     m_event( std::make_shared<SDL_Event>())
{

    using namespace std;

    try
    {
        if( TTF_Init() != 0 ){
            string s("TTF_Init error: " );
            s.append(SDL_GetError());
            throw runtime_error(s);
        }

        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            string s("SDL_Init error: " );
            s.append(SDL_GetError());
            throw runtime_error(s);
        }

        auto window_deleter = [](SDL_Window* window) {
          if(window==nullptr) delete window;
        };


        Uint32 show = m_show ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN;
        m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("SDL_TETRIS",
                                                                SDL_WINDOWPOS_UNDEFINED,
                                                                SDL_WINDOWPOS_UNDEFINED,
                                                                m_windowWidth,
                                                                m_windowHeight,
                                                                show), window_deleter);

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

void Window::show()
{
    SDL_ShowWindow(m_window.get());
}

void Window::hidden()
{
    SDL_HideWindow(m_window.get());
}
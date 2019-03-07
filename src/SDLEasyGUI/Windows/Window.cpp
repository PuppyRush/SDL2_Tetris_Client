//
// Created by chaed on 18. 12. 24.
//

#include <iostream>

#include "Window.h"

using namespace sdleasygui;

Window::Window()
    :m_windowHeight(WINDOW_HEIGHT),
     m_windowWidth(WINDOW_WIDTH)
{

    using namespace std;

    try
    {

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

        if(m_window.get() == nullptr)
        {
            assert(0);
        }

        auto renderer_deleter = [](SDL_Renderer* window) {
          if(window==nullptr) delete window;
        };

        m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(),
                                                                      -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
            , renderer_deleter);

        m_windowID = SDL_GetWindowID(m_window.get());

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

Window::~Window()
{

}

void Window::show()
{
    SDL_ShowWindow(m_window.get());
}

void Window::hidden()
{
    SDL_HideWindow(m_window.get());
}


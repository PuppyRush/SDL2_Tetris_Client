//
// Created by chaed on 18. 12. 24.
//

#include <iostream>

#include "include/SEG_Window.h"

using namespace seg;

SEG_Window::SEG_Window(const t_size width, const t_size height)
        : m_windowHeight(height),
          m_windowWidth(width),
          m_window(nullptr),
          m_renderer(nullptr)
{

}

SEG_Window::~SEG_Window()
{
    if(m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if(m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if(m_window) {
        delete m_window;
        m_window = nullptr;
    }
    if(m_renderer) {
        delete m_renderer;
        m_renderer = nullptr;
    }
}

void SEG_Window::initialize()
{
    using namespace std;

    try {

        Uint32 show = m_show ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN;
		show |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

        if (m_resizable)
        {
            show |= SDL_WINDOW_RESIZABLE;
        }
        if (m_isBorder)
        {
            show |= SDL_WINDOW_BORDERLESS;
        }

        m_window = SDL_CreateWindow(m_title.c_str(), 
									SDL_WINDOWPOS_UNDEFINED, 
									SDL_WINDOWPOS_UNDEFINED, 
									m_windowWidth,
                                    m_windowHeight,
                                    show);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        m_windowID = SDL_GetWindowID(m_window);

    }
    catch (std::runtime_error& e) {
        std::cerr << e.what();
    }
    catch (...) {
        std::cerr << "fail tetris game GameInterface_Init because of unkwon error ";
    }
}

void SEG_Window::setHeight(const t_size height) noexcept
{
    m_windowHeight = height;
    SDL_SetWindowSize(m_window, m_windowWidth, height);

}

void SEG_Window::setWidth(const t_size width) noexcept
{
    m_windowWidth = width;
    SDL_SetWindowSize(m_window, width, m_windowHeight);
}

void SEG_Window::setTitle(const std::string& title)
{
    m_title = title;
    SDL_SetWindowTitle(m_window, title.c_str());
}

void SEG_Window::show()
{
    SDL_ShowWindow(m_window);
}

void SEG_Window::hidden()
{
    SDL_HideWindow(m_window);
}

void SEG_Window::maximize()
{
    SDL_MaximizeWindow(m_window);
}

void SEG_Window::minimized()
{
    SDL_MinimizeWindow(m_window);
}

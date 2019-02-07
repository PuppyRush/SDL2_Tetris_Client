//
// Created by chaed on 18. 12. 24.
//

#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "../TType.h"
#include "../TStruct.h"

SDL_TETRIS_BEGIN

class Window final
{

public:

    Window();

    inline void setShow(const bool b){m_show = b;}
    void show();
    void hidden();

    inline const size_t getDisplayWidth() const noexcept { return m_windowWidth; }
    inline const size_t getDisplayHeight() const noexcept{ return m_windowHeight; }

    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept
    {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getSDLRenderer() const noexcept
    {
        return m_renderer;
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept
    {
        return m_event;
    }

private:

    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::shared_ptr<SDL_Event> m_event;

    const tetris::t_size m_windowWidth;
    const tetris::t_size m_windowHeight;

    bool m_show = false;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWINDOW_H

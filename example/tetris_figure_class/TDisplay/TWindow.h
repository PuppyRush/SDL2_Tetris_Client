//
// Created by chaed on 18. 12. 24.
//

#ifndef TETRIS_FIGURE_CLASS_TWINDOW_H
#define TETRIS_FIGURE_CLASS_TWINDOW_H

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "Common/THeader.h"

SDL_TETRIS_BEGIN

class TWindow final
{

public:

    inline const size_t getDisplayWidth() const noexcept { return m_windowWidth; }
    inline const size_t getDisplayHeight() const noexcept{ return m_windowHeight; }

    inline std::shared_ptr<SDL_Window> getWindow() const noexcept
    {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept
    {
        return m_renderer;
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept
    {
        return m_event;
    }

    static std::shared_ptr<TWindow> getInstance();

private:

    TWindow();

    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::shared_ptr<SDL_Event> m_event;

    const tetris::t_size m_windowWidth;
    const tetris::t_size m_windowHeight;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWINDOW_H

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

#include "SDLEasyGUI/SEG_TType.h"
#include "SDLEasyGUI/SEG_TStruct.h"

class Window final
{

public:

    Window();

    inline void setShow(const bool b){m_show = b;}
    void show();
    void hidden();

    inline const size_t getDisplayWidth() const noexcept { return m_windowWidth; }
    inline const size_t getDisplayHeight() const noexcept{ return m_windowHeight; }
    inline const t_winid getWindowID() const noexcept{ return m_windowID; }


    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept
    {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getSDLRenderer() const noexcept
    {
        return m_renderer;
    }

private:

    std::shared_ptr<SDL_Window> m_window = nullptr;
    std::shared_ptr<SDL_Renderer> m_renderer = nullptr;

    const t_size m_windowWidth=0;
    const t_size m_windowHeight=0;
    Uint32 m_windowID;
    bool m_show = false;
};

#endif //TETRIS_FIGURE_CLASS_TWINDOW_H

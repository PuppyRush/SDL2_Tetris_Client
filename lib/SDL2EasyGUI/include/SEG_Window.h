//
// Created by chaed on 18. 12. 24.
//

#ifndef SDL2EASYGUI_WINDOW_H
#define SDL2EASYGUI_WINDOW_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "SEG_Struct.h"
#include "SEG_Constant.h"

namespace seg {

class SEG_Window final
{

public:

    using unique_type = t_id;
    using window_type = SDL_Window*;
    using renderer_type = SDL_Renderer*;

    SEG_Window(const t_size width = WINDOW_WIDTH, const t_size height = WINDOW_HEIGHT);

    virtual ~SEG_Window();

    void setTitle(const std::string& title);

    void setWidth(t_size width) noexcept;

    void setHeight(t_size height) noexcept;

    inline void setShow(bool b) noexcept
    {
        m_show = b;
    }

    inline void setResizable(bool b) noexcept
    {
        m_resizable = b;
        SDL_SetWindowResizable(m_window, b ? SDL_TRUE : SDL_FALSE);
    }

    inline void setBorder(bool b) noexcept
    {
        m_isBorder = b;
        SDL_SetWindowBordered(m_window, b ? SDL_TRUE : SDL_FALSE);
    }

    void show();

    void hidden();

    void maximize();

    void minimized();

    void initialize();


    inline bool getResizable() const noexcept
    {
        return m_windowWidth;
    }

    inline bool getBorder() const noexcept
    {
        return m_isBorder;
    }

    inline t_size getWidth() const noexcept
    {
        return m_windowWidth;
    }

    inline t_size getHeight() const noexcept
    {
        return m_windowHeight;
    }

    inline t_id getWindowID() const noexcept
    { return m_windowID; }

    inline window_type getWindow() const noexcept
    {
        return m_window;
    }

    inline renderer_type getRenderer() const noexcept
    {
        return m_renderer;
    }

private:

    renderer_type m_renderer = nullptr;
    window_type m_window = nullptr;

    t_size m_windowWidth = 0;
    t_size m_windowHeight = 0;
    std::string m_title;
    t_id m_windowID = NULL_WINDOW_ID;
    bool m_show = false;
    bool m_isBorder = true;
    bool m_resizable = false;
};

}

#endif //SDL2EASYGUI_TWINDOW_H

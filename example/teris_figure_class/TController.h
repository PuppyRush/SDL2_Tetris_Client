//
// Created by chaed on 18. 12. 15.
//

#ifndef TERIS_FIGURE_CLASS_TCONTROLLER_H
#define TERIS_FIGURE_CLASS_TCONTROLLER_H

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

#include "Common/TDefine.h"
#include "Common/TType.h"
#include "Common/TProperty.h"

SDL_TETRIS_BEGIN

class TControllerInterface
{
public:
    virtual ~TControllerInterface()

    void show();
    void hide();



protected:
    TControllerInterface()
    :m_windowHeight(DISPLAY_HEIGHT),
    m_windowWidth(DISPLAY_WIDTH),
    m_event(new SDL_Event())
    {}

    inline SDL_Window* getWindow() const {
        return m_window;
    }

    inline SDL_Renderer* getRenderer() const
    {
        return m_renderer;
    }

    inline SDL_Event* getSDLEvent() const
    {
        return m_event;
    }

private:
    const t_size m_windowWidth;
    const t_size m_windowHeight;

    virtual void _setDisplay() = 0;
    SDL_Window* m_window = SDL_CreateWindow("SDL_TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event* m_event;
};


SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_TCONTROLLER_H

//
// Created by chaed on 19. 3. 17.
//

#include "GraphicInterface.h"

using namespace seg;

GraphicInterface::GraphicInterface(window_type window)
    :m_window(window)
{}

GraphicInterface::GraphicInterface(const std::shared_ptr<ControlData>& ctl)
        : GraphicInterface(ctl->window)
{
    m_data = ctl;
}

GraphicInterface::~GraphicInterface()
{
    if (m_window) {
        delete m_window;
        m_window = nullptr;
    }
}

void GraphicInterface::onDraw()
{
    _release();
}

void GraphicInterface::_drawBackground(const SDL_Rect rect)
{
    auto renderer = getRenderer();

    const auto& back_color = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void GraphicInterface::_release()
{
    auto renderer = getRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
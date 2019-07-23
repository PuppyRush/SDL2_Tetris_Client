//
// Created by chaed on 19. 3. 17.
//

#include "GraphicInterface.h"

using namespace sdleasygui;

GraphicInterface::GraphicInterface()
        : m_window(), m_positionRect({0, 0, 0, 0})
{}

GraphicInterface::~GraphicInterface()
{
    if (m_window) {
        delete m_window;
        m_window = nullptr;
    }
}

void GraphicInterface::_drawBackground(const SDL_Rect rect)
{
    auto renderer = getWindow()->getSDLRenderer();

    const auto& back_color = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

//
// Created by chaed on 19. 3. 17.
//

#include "GraphicInterface.h"

using namespace seg;

GraphicInterface::GraphicInterface()
{}

GraphicInterface::GraphicInterface(std::shared_ptr<ControlBasic> ctl)
        : m_window(ctl->window), m_data(ctl)
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

bool GraphicInterface::_hitTest(const SDL_Rect& rect,const SEG_Point& point) const  _GLIBCXX_NOEXCEPT
{
    if ((rect.x <= point.x && point.x <= rect.x + rect.w) && (rect.y <= point.y && point.y <= rect.y + rect.h)) {
        return true;
    } else {
        return false;
    }
}

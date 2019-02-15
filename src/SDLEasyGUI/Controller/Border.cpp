//
// Created by chaed on 19. 1. 22.
//

#include "Border.h"


Border::Border(const BorderBuilder& basic)
    :Controll(basic ,TControllKind::Border),
    m_borderBasic{basic.m_borderBasic}
{

}

void Border::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer().get();

    switch(m_borderBasic.type)
    {
        case BorderBoundaryType::angle: {
            SDL_Rect rect{getPoint().x, getPoint().y, getWidth(), getHeight()};

            const auto &back_color = getBackground_color();

            SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);
            SDL_RenderFillRect(renderer, &rect);
            //SDL_RenderDrawRect(renderer, &rect);
        }
        break;
        case BorderBoundaryType::ellipse:
            assert(0);
            break;

        case BorderBoundaryType::round:
            assert(0);
            break;
    }
}

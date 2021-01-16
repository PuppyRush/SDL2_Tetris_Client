//
// Created by chaed on 19. 1. 22.
//

#include <sdl2gfx/SDL2_gfxPrimitives.h>

#include "Border.h"

using namespace seg;

Border::Border(ControlBuilder& basic)
        : Control(basic)
{
    basic.kind(ControlKind::Border);
}

void Border::initialize()
{
    Control::initialize();
}

void Border::onDrawBackground()
{
    Control::onDrawBackground();
}

void Border::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    const int x = getPoint().x;
    const int y = getPoint().y;
    const int w = getWidth();
    const int h = getHeight();
    const auto& lineColor = getBorderLineColor();

    switch (getBorderBoundaryType()) {
        case BorderBoundaryType::angle: {
            const size_t cnt{5};
            for (int i = 0; i < getBorderThick(); i++) {
                SDL_Point points[cnt] =
                        {{x + i,     y + i},
                         {x + w - i, y + i},
                         {x + w - i, y + h - i},
                         {x + i,     y + h - i},
                         {x + i,     y + i}};

                SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, 255);
                SDL_RenderDrawLines(renderer, points, cnt);
            }
        }
            break;
        case BorderBoundaryType::roundedAngle:
            for (int i = 0; i < getBorderThick(); i++) {
                roundedRectangleRGBA(renderer, x + i, y + i, x + w - i, y + h - i, getBorderAngle(),
                                     lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            }

            break;
        case BorderBoundaryType::ellipse:
            ellipseRGBA(renderer, x + w / 2, y + h / 2, getTextWidth() / 2, getTextHeight() / 2,
                        lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            break;

        case BorderBoundaryType::round: {

            circleRGBA(renderer, x + w / 2, y + h / 2, std::max(getTextWidth() / 2, getTextHeight() / 2),
                       lineColor.r, lineColor.g, lineColor.b, lineColor.a);
            break;
        }
    }
    Control::onDraw();
}

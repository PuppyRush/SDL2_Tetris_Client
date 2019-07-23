//
// Created by chaed on 19. 7. 4.
//

#ifndef SDL2_TETRIS_CLIENT_SEG_DRAWER_H
#define SDL2_TETRIS_CLIENT_SEG_DRAWER_H


#if _MSC_VER >= 1200
#pragma once
#endif


#include "SEG_Struct.h"
#include "sdl2gfx/SDL2_gfxPrimitives.h"

namespace sdleasygui {

static void SEG_DrawRoundedRactangel(SDL_Renderer* renderer, const SDL_Rect rect, const SEG_Color& color, int16_t rad)
{
    roundedRectangleRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, rad, color.r, color.g, color.b, color.a);
}


static void SEG_DrawCircle(SDL_Renderer* renderer, const SEG_Point midPoint, const SEG_Color& color, const size_t thick = 1)
{
    filledCircleRGBA(renderer,midPoint.x, midPoint.y, thick, color.r, color.g, color.b, color.a);
}

static void SEG_DrawX(SDL_Renderer* renderer, const SDL_Rect rect, const SEG_Color& color, const size_t thick = 1)
{
    SDL_Point line1[2]{{rect.x, rect.y},{rect.x + rect.w, rect.y + rect.h}};
    SDL_Point line2[2]{{rect.x + rect.w, rect.y},{rect.x , rect.y + rect.h}};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
            color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
                  color.r, color.g, color.b, color.a);

}

static void SEG_DrawV(SDL_Renderer* renderer, const SDL_Rect rect, const SEG_Color& color, const size_t thick = 1)
{
    SDL_Point line1[2]{{rect.x + rect.w/4, rect.y + rect.h/6},{rect.x + (rect.w/2), rect.y + rect.h - rect.h/5}};
    SDL_Point line2[2]{{rect.x + (rect.w/2), rect.y + rect.h - rect.h/5},{rect.x + rect.w, rect.y }};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
                  color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
                  color.r, color.g, color.b, color.a);

}


class TextDrawer
{

public:

    TextDrawer(SDL_Renderer* renderer, const SEG_TFont& fontinfo, const SEG_Point& point, const std::string& str)
            : m_textSurface(nullptr), m_point(point), m_renderer(renderer)
    {
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        SDL_Color textColor = {fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0};

        m_textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
        m_texture = SDL_CreateTextureFromSurface(renderer, m_textSurface);

        if (m_textSurface != nullptr) {
            m_height = static_cast<double>(m_textSurface->h);
            m_width = static_cast<double>(m_textSurface->w);
        }
    }

    ~TextDrawer()
    {
        SDL_FreeSurface(m_textSurface);
    }

    void drawText()
    {
        if (m_texture != nullptr) {
            SDL_Rect renderQuad =
                    {static_cast<int>(m_point.x), static_cast<int>(m_point.y), static_cast<int>(m_width),
                     static_cast<int>(m_height)};
            SDL_RenderCopy(m_renderer, m_texture, nullptr, &renderQuad);
        }

    }

    inline const SDL_Texture* getTexture()
    { return m_texture; }

    inline const SDL_Surface* getTextSurface()
    { return m_textSurface; }

    inline double getTextWidth()
    {
        return m_textSurface ?
               static_cast<double>(m_textSurface->w) : 0;
    }

    inline double getTextHeight()
    {
        return m_textSurface ?
               static_cast<double>(m_textSurface->h) : 0;
    }

    inline void setPoint(const SEG_Point& point)
    { m_point = point; }

private:

    SDL_Surface* m_textSurface;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;
    SEG_Point m_point;
    double m_height;
    double m_width;

};


}
#endif //SDL2_TETRIS_CLIENT_SEG_DRAWER_H

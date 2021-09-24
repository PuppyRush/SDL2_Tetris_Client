//
// Created by chaed on 19. 7. 4.
//

#ifndef SDL2_TETRIS_CLIENT_SEG_DRAWER_H
#define SDL2_TETRIS_CLIENT_SEG_DRAWER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "SEG_TypeTraits.h"
#include "SEG_Struct.h"

namespace seg::drawer {

    static void draw_Triangle(SDL_Renderer* renderer,SEG_Point p1, SEG_Point p2, SEG_Point p3,
        const SEG_Color& color)
    {
        trigonRGBA(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a);
    }

    static void
        draw_FilledTriangle(SDL_Renderer* renderer, SEG_Point p1, SEG_Point p2, SEG_Point p3,
            const SEG_Color& color)
    {
        filledTrigonRGBA(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a);
    }

    static void draw_RoundedRactangel(SDL_Renderer* renderer, SDL_Rect rect, SEG_Color color, int16_t rad,
        t_size thick = 1)
    {
        auto copied{ rect };
        for (t_size t = 0; t < thick; t++) {
            copied.x += t;
            copied.y += t;
            copied.h -= (t + 1);
            copied.w -= (t + 1);
            roundedRectangleRGBA(renderer, copied.x, copied.y, copied.x + copied.w, copied.y + copied.h, rad, color.r,
                color.g, color.b,
                color.a);
        }
    }

    static void
        draw_FilledRoundedRactangel(SDL_Renderer* renderer, SDL_Rect rect, SEG_Color color, int16_t rad)
    {
        roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, rad, color.r, color.g, color.b,
            color.a);
    }

    static void
        drawThickLine(SDL_Renderer* renderer, SEG_Point p1, SEG_Point p2, SEG_Color color,
            const size_t thick = 1)
    {
        thickLineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, thick, color.r, color.g, color.b, color.a);
    }

    static void
        drawCircle(SDL_Renderer* renderer, SEG_Point midPoint, SEG_Color color, size_t thick = 1)
    {
        filledCircleRGBA(renderer, midPoint.x, midPoint.y, thick, color.r, color.g, color.b, color.a);
    }

    static void drawX(SDL_Renderer* renderer, SDL_Rect rect, SEG_Color color, size_t thick = 1)
    {
        SDL_Point line1[2]{ {rect.x,          rect.y},
                           {rect.x + rect.w, rect.y + rect.h} };
        SDL_Point line2[2]{ {rect.x + rect.w, rect.y},
                           {rect.x,          rect.y + rect.h} };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
            color.r, color.g, color.b, color.a);

        thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
            color.r, color.g, color.b, color.a);
    }

    static void drawV(SDL_Renderer* renderer, SDL_Rect rect, SEG_Color color, size_t thick = 1)
    {
        SDL_Point line1[2]{ {rect.x + rect.w / 4,   rect.y + rect.h / 6},
                           {rect.x + (rect.w / 2), rect.y + rect.h - rect.h / 5} };
        SDL_Point line2[2]{ {rect.x + (rect.w / 2), rect.y + rect.h - rect.h / 5},
                           {rect.x + rect.w,       rect.y} };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
            color.r, color.g, color.b, color.a);

        thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
            color.r, color.g, color.b, color.a);
    }

    using color_type = std::underlying_type_t<ColorCode>;

    static SDL_Color getColor(const ColorCode colorCode)
    {
        SEG_Color col(colorCode);
        SDL_Color color{ col.r, col.g, col.b, 255 };
        return color;
    }

    static SDL_Color getTransparent()
    {
        SEG_Color col(ColorCode::white);
        SDL_Color color{ col.r, col.g, col.b, 0 };
        return color;
    }

    static ColorCode getInvertedColor(const ColorCode colodeCode)
    {
        return ColorCode((static_cast<color_type>(colodeCode)) ^ 0xffffff);
    }

    static ColorCode getInvertedColor(const SEG_Color& color)
    {
        return getInvertedColor(color.colorCode);
    }

    class TextDrawer //: private boost::serialization::singleton<TextDrawer>
    {

    public:

        friend class boost::serialization::singleton<TextDrawer>;

        TextDrawer() = default;

        TextDrawer(SDL_Renderer* renderer, const SEG_TFont& fontinfo, const SEG_Point& point, const std::string& str)
            : m_textSurface(nullptr),  m_renderer(renderer), m_text(str), m_font(fontinfo)
        {
            m_dstrect.x = point.x;
            m_dstrect.y = point.y;
            _setTextTexture(str);
        }

        ~TextDrawer()
        {
            SDL_FreeSurface(m_textSurface);
        }

        void drawText()
        {
            if (m_isTextEmpty == true)
            {
                return;
            }

            SDL_SetRenderTarget(m_renderer, nullptr);
            //if(m_srcrect.w == m_dstrect.w  && m_srcrect.h == m_dstrect.h)
            //{
            //    SDL_RenderCopy(m_renderer, m_srcTexture, nullptr, &m_dstrect);
            //}
            //else
            //{
            SDL_RenderCopy(m_renderer, m_srcTexture, &m_srcrect, &m_dstrect);
            //}
            SDL_SetRenderTarget(m_renderer, nullptr);

        }

        SEG_Color getColor() const noexcept
        {
            return m_font.color;
        }

        void setColor(const SEG_Color& color)
        {
            m_font.color = color;
        }

        std::string getFontName() const noexcept
        {
            return m_font.fontName;
        }

        void setFontName(const std::string& str)
        {
            m_font.fontName = str;
        }

        void setFont(const SEG_TFont& font)
        {
            m_font = font;
        }

        SEG_TFont getFont() const noexcept
        {
            return m_font;
        }

        void setRenderer(SDL_Renderer* rend)
        {
            m_renderer = rend;
        }

        inline t_coord getPositionX() const noexcept
        {
            return  m_dstrect.x;
        }

        void setPositionX(const t_coord coord)
        {
            m_dstrect.x = coord;
        }

        inline t_coord getPositionY() const noexcept
        {
            return m_dstrect.y;
        }

        void setPositionY(const t_coord coord)
        {
            m_dstrect.y = coord;
        }

        void setPosition(const SDL_Rect rect)
        {
            m_srcrect.w = rect.w;
            m_srcrect.h = rect.h;
            m_dstrect = rect;
        }

        inline SDL_Rect getPosition() const noexcept
        {
            return m_dstrect;
        }

        const std::string& getText() const noexcept
        {
            return m_text;
        }

        void setText(std::string&& str)
        {
            m_text = str;
            _setTextTexture(str);
        }

        void setText(const std::string& str)
        {
            m_text = str;
            _setTextTexture(str);
        }

        inline int getTextWidth() const noexcept
        {
            return  m_dstrect.w;
        }

        inline int getTextHeight() const noexcept
        {
            return  m_dstrect.h;
        }

        inline void setTextWidth(const t_size w)
        {
            m_srcrect.w = w;
            m_dstrect.w = w;
        }

        inline void setTextHeight(const t_size h)
        {
            m_srcrect.h = h;
            m_dstrect.h = h;
        }

        inline t_size getSize() const noexcept
        {
            return m_font.size;
        }

        inline void setSize(t_size size)
        {
            m_font.size = size;
        }

        inline SEG_Point getPoint() const noexcept
        {
            return make_segpoint(m_dstrect.x, m_dstrect.y);
        }

        inline void setPoint(const SEG_Point point)
        {
            m_dstrect.x = point.x;
            m_dstrect.y = point.y;
        }

        inline SEG_Color getBackgroundColor() const noexcept
        {
            return m_backgroundColor;
        }

        inline void setBackgroundColor(SEG_Color color)
        {
            m_backgroundColor = color;
        }

    private:

        void _setTextTexture(const std::string& str)
        {
            if (str.empty())
            {
                m_isTextEmpty = true;
                return;
            }

            TTF_Font* font = TTF_OpenFont(m_font.fontName.c_str(), m_font.size);
            SDL_Color textColor = { m_font.color.r, m_font.color.g, m_font.color.b, m_font.color.a };

            m_textSurface = TTF_RenderUTF8_Solid(font, str.c_str(), textColor);

            if (m_textSurface != nullptr)
            {
                m_srcTexture = SDL_CreateTextureFromSurface(m_renderer, m_textSurface);
                m_isTextEmpty = m_srcTexture == nullptr;
                m_srcrect = { 0, 0, m_textSurface->w, m_textSurface->h };
                m_dstrect.w = m_textSurface->w;
                m_dstrect.h = m_textSurface->h;
            }
        }

    private:

        SDL_Surface* m_textSurface = nullptr;
        SDL_Texture* m_srcTexture = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        SEG_Color m_backgroundColor{ ColorCode::white };
        SEG_TFont m_font;
        SDL_Rect m_dstrect;
        SDL_Rect m_srcrect;
        std::string m_text;
        bool m_isTextEmpty = true;
    };


    static std::pair<int,int> getTextSize(TTF_Font* font, const std::string& str) 
    {
        int* h = new int;
        int* w = new int;
        assert(font != nullptr);
        assert(h != nullptr);
        assert(w != nullptr);
        TTF_SizeText(font, str.c_str(), w, h);

        std::pair<int, int> wh = std::make_pair(*w, *h);
        delete h;
        delete w;
        return wh;


    }
}

#endif //SDL2_TETRIS_CLIENT_SEG_DRAWER_H

//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Tetris/Common/TDefine.h"
#include "Window.h"
#include "EventListener.h"
#include "EventDelivery.h"


namespace sdleasygui {

class GraphicInterface : public EventListener, public EventDelivery {

public:
    using window_ptr = std::shared_ptr<Window>;

    virtual ~GraphicInterface() = default;
    virtual void onDraw() = 0;

    void setWindow(window_ptr window) { m_window = window; }
    window_ptr getWindow() const noexcept {  return m_window;  }

protected:

    GraphicInterface() = default;
    virtual void refresh() = 0;

private:

    virtual bool validId(const game_interface::t_id id) = 0;

    window_ptr m_window = nullptr;

};

class textDrawer
{
    SDL_Surface* textSurface;
    SDL_Texture* texture;
public:

    textDrawer(SDL_Renderer* renderer, const TFont& fontinfo, const std::string str)
        :textSurface(nullptr)
    {
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

        textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    }

    inline SDL_Texture* getTexture() { return texture;}
    inline SDL_Surface* getTextSurface() { return textSurface;}

    ~textDrawer()
    {
        SDL_FreeSurface(textSurface);
    }
};


}

#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
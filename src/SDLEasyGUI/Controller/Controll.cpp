//
// Created by chaed on 18. 12. 26.
//

#include "Controll.h"

Controll::Controll(const ControllBuilder& bld, const TControllKind kind)
{
    m_basic = std::make_shared<ControllBasic>(bld.getBasic());
    m_basic->kind = kind;
    setWindow(bld.getWindow());

}

void Controll::initialize()
{
    setSelected(m_basic->selected);

    if(m_basic->group != GroupControllManager::NONE)
    {
        GroupControllManager::getInstance()->add(m_basic->group, m_basic->id);
        if(m_basic->multiselected)
            GroupControllManager::getInstance()->setMultiselect(m_basic->group);
    }
}

void Controll::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer().get();
    const auto& fontinfo = getFont();
    TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
    std::string score_text = getName();
    SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    const double text_width = static_cast<double>(textSurface->w);
    const double text_height = static_cast<double>(textSurface->h);

    SDL_Rect rect;
    if(getAutoSize())
        rect = SDL_Rect{ getPoint().x-20,
                         getPoint().y,
                         static_cast<int>(text_width*1.2),
                         static_cast<int>(text_height*1.4)};
    else
        rect = SDL_Rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};

    const auto& back_color = getBackground_color();

    SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_Rect renderQuad = { static_cast<int>(getPoint().x + ( getWidth() - text_width)/2)
        , static_cast<int>(getPoint().y + ( getHeight() - text_height)/2)
        , static_cast<int>(text_width)
        , static_cast<int>(text_height) };
    SDL_RenderCopy(renderer, text, nullptr, &renderQuad);

}



void Controll::setSelected(bool selected)
{
    m_basic->selected = selected;
    if(selected)
        GroupControllManager::getInstance()->select(m_basic->group, m_basic->id);
}

const bool Controll::isHit(const TPoint& point)
{
    const auto& menu_point = m_basic->point;
    if (this->isEnabled() && (menu_point.x <= point.x && point.x <= menu_point.x + m_basic->width)
        && (menu_point.y <= point.y && point.y <= menu_point.y + m_basic->height)) {
        setSelected(!isSelected());

        SDL_UserEvent userevent;
        userevent.type = SDL_CLICKED_CONTROLLER;
        userevent.code = this->getId();

        SDL_Event event;
        event.type = SDL_CLICKED_CONTROLLER;
        event.user = userevent;

        SDL_PushEvent(&event);

        return true;
    }
    else {
        return false;
    }
}

bool Controll::validId(const t_id id)
{
    return getId() == id;
}

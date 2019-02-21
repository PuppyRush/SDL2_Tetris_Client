//
// Created by chaed on 18. 12. 26.
//

#include "Controll.h"

Controll::Controll(const ControllBuilder& bld)
{
    m_basic = std::make_shared<ControllBasic>(bld.getBasic());
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

void Controll::onKeyboardEvent (const SDL_KeyboardEvent* key)
{
    refresh();
}

void Controll::onTextInputEvent (const SDL_TextInputEvent* text)
{
    refresh();
}

void Controll::onVirtualDraw()
{
    onDrawBackground();
    onDraw();
}


void Controll::refresh()
{
    SDL_UserEvent userevent;
    userevent.type = SDL_DRAW_CONTROLLER  ;
    userevent.code = this->getId();
    userevent.windowID = this->getWindow()->getWindowID();

    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
}

void Controll::setSelected(bool selected)
{
    m_basic->selected = selected;
    if(selected)
        GroupControllManager::getInstance()->select(m_basic->group, m_basic->id);
}

const bool Controll::isHit(const Point& point)
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

bool Controll::validId(const game_interface::t_id id)
{
    return getId() == id;
}

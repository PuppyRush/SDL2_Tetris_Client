//
// Created by chaed on 18. 12. 22.
//

#include "TMenuBuilder.h"

SDL_TETRIS

TMenuBuilder::TMenuBuilder()
    :m_currentMenu(std::make_shared<TMenu>())
{
}

TMenuBuilder* TMenuBuilder::name(const std::string& name)
{
    m_currentMenu->name = name;
    return this;
}

TMenuBuilder* TMenuBuilder::font(const TFont& font)
{
    m_currentMenu->font = font;
    return this;
}

TMenuBuilder* TMenuBuilder::point(const TPoint& point)
{
    m_currentMenu->point = point;
    return this;
}

TMenuBuilder* TMenuBuilder::eanbled(const bool enable)
{
    m_currentMenu->enabled = enable;
    return this;
}

TMenuBuilder* TMenuBuilder::add()
{
    m_menus.emplace_back(m_currentMenu);
    m_currentMenu.reset();
    m_currentMenu = std::make_shared<TMenu>();
    return this;
}

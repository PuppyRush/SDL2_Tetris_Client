//
// Created by chaed on 18. 12. 22.
//

#include "TMenuBuilder.h"

SDL_TETRIS

TMenuBuilder::TMenuBuilder()
    :m_currentMenu(std::make_shared<TMenu>())
{
    m_menus = container_type([](const value_type& lhs, const value_type& rhs) -> bool
    {
       return lhs->point.y < rhs->point.y ||
       lhs->point.x < rhs->point.x ||
       lhs->height < rhs->height;
    });
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

TMenuBuilder* TMenuBuilder::width(const t_size size)
{
    this->m_currentMenu->width = size;
    return this;

}

TMenuBuilder* TMenuBuilder::height(const t_size size)
{
    this->m_currentMenu->height = size;
    return this;
}

TMenuBuilder* TMenuBuilder::enabled(const bool enable)
{
    m_currentMenu->enabled = enable;
    return this;
}


TMenuBuilder* TMenuBuilder::display(const TDisplay display)
{
    m_currentMenu->display = display;
    return this;
}

TMenuBuilder* TMenuBuilder::add()
{
    m_menus.insert( m_currentMenu);
    m_currentMenu.reset();
    m_currentMenu = std::make_shared<TMenu>();
    return this;
}

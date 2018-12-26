//
// Created by chaed on 18. 12. 22.
//

#include "TControllBuilder.h"

SDL_TETRIS

TControllBuilder::TControllBuilder()
    :m_currentMenu(std::make_shared<TControll>())
{
    m_menus = container_type([](const value_type& lhs, const value_type& rhs) -> bool
    {
       return lhs->getPoint().y < rhs->getPoint().y ||
       lhs->getPoint().x < rhs->getPoint().x ||
       lhs->getHeight() < rhs->getHeight();
    });
}

TControllBuilder* TControllBuilder::name(const std::string& name)
{
    m_currentMenu->setName(name);
    return this;
}

TControllBuilder* TControllBuilder::font(const TFont& font)
{
    m_currentMenu->setFont(font);
    return this;
}

TControllBuilder* TControllBuilder::point(const TPoint& point)
{
    m_currentMenu->setPoint(point);
    return this;
}

TControllBuilder* TControllBuilder::background_color(const TColorCode color)
{
    m_currentMenu->setBackground_color(TColor{color});
    return this;
}

TControllBuilder* TControllBuilder::width(const t_size size)
{
    this->m_currentMenu->setWidth(size);
    return this;

}

TControllBuilder* TControllBuilder::height(const t_size size)
{
    this->m_currentMenu->setHeight(size);
    return this;
}

TControllBuilder* TControllBuilder::enabled(const bool enable)
{
    m_currentMenu->setEnabled(enable);
    return this;
}


TControllBuilder* TControllBuilder::display(const TDisplay display)
{
    m_currentMenu->setDisplay(display);
    return this;
}

TControllBuilder* TControllBuilder::multiselected(const bool selected)
{
    m_currentMenu->setMultiselected( selected);
    return this;
}

TControllBuilder* TControllBuilder::kind(const TOption option)
{
    m_currentMenu->setKind( option);
    return this;
}

TControllBuilder* TControllBuilder::grouping(const size_t idx)
{
    m_currentMenu->setGroup(idx);
    return this;
}

TControllBuilder* TControllBuilder::carot()
{
    m_currentMenu->setCarot(true);
    return this;
}

TControllBuilder* TControllBuilder::add()
{
    m_menus.insert( m_currentMenu);
    m_currentMenu.reset();
    m_currentMenu = std::make_shared<TControll>();
    return this;
}

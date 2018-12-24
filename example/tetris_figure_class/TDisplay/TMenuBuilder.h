//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TMENUBUILDER_H
#define TETRIS_FIGURE_CLASS_TMENUBUILDER_H

#include <set>
#include <functional>
#include <memory>

#include "THeader.h"

SDL_TETRIS_BEGIN

class TMenuBuilder
{
public:

    using value_type = std::shared_ptr<TMenu>;
    using comp_type = std::function<bool(const value_type& lhs, const value_type& rhs)>;
    using container_type = std::set<value_type, comp_type>;

    TMenuBuilder();

    TMenuBuilder* name(const std::string& name);
    TMenuBuilder* font(const TFont& font);
    TMenuBuilder* width(const t_size size);
    TMenuBuilder* height(const t_size size);
    TMenuBuilder* point(const TPoint& point);
    TMenuBuilder* display(const TDisplay display);
    TMenuBuilder* enabled(const bool enable);
    TMenuBuilder* add();

    inline const container_type& getMenus() const noexcept
    { return m_menus;}

private:

    container_type m_menus;
    value_type m_currentMenu;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

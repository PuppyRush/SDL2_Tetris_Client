//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TMENUBUILDER_H
#define TETRIS_FIGURE_CLASS_TMENUBUILDER_H

#include <set>
#include <functional>
#include <memory>

#include "THeader.h"
#include "TControll/TControll.h"

SDL_TETRIS_BEGIN

class TControllBuilder final
{
public:

    using value_type = std::shared_ptr<TControll>;
    using comp_type = std::function<bool(const value_type& lhs, const value_type& rhs)>;
    using container_type = std::set<value_type, comp_type>;

    TControllBuilder();

    TControllBuilder* name(const std::string& name);
    TControllBuilder* font(const TFont& font);
    TControllBuilder* background_color(const TColorCode color);
    TControllBuilder* width(const t_size size);
    TControllBuilder* height(const t_size size);
    TControllBuilder* point(const TPoint& point);
    TControllBuilder* display(const TDisplay display);
    TControllBuilder* enabled(const bool enable);
    TControllBuilder* multiselected(const bool selected);
    TControllBuilder* kind(const TOption option);
    TControllBuilder* grouping(const size_t idx);
    TControllBuilder* carot();
    TControllBuilder* add();

    inline const container_type& getMenus() const noexcept
    { return m_menus;}

private:

    container_type m_menus;
    value_type m_currentMenu;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

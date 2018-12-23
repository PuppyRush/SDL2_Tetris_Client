//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TMENUBUILDER_H
#define TETRIS_FIGURE_CLASS_TMENUBUILDER_H

#include <vector>
#include <memory>

#include "THeader.h"

SDL_TETRIS_BEGIN

class TMenuBuilder
{
public:

    TMenuBuilder();

    TMenuBuilder* name(const std::string& name);
    TMenuBuilder* font(const TFont& font);
    TMenuBuilder* point(const TPoint& point);
    TMenuBuilder* eanbled(const bool enable);
    TMenuBuilder* add();

    inline const std::vector<std::shared_ptr<TMenu>>& getMenus() const noexcept
    { return m_menus;}

private:
    std::vector<std::shared_ptr<TMenu>> m_menus;
    std::shared_ptr<TMenu> m_currentMenu;
};


SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

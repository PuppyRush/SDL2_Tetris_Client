//
// Created by chaed on 18. 12. 22.
//

#ifndef TETRIS_FIGURE_CLASS_TMENUBUILDER_H
#define TETRIS_FIGURE_CLASS_TMENUBUILDER_H

#include <set>
#include <functional>
#include <memory>
#include <atomic>

#include "THeader.h"
#include "../TOption/TOptionManager.h"

SDL_TETRIS_BEGIN

class TControllBuilder final
{
public:

    TControllBuilder(const TPoint& point, const std::string& str);
    TControllBuilder(TPoint&& point, std::string&& str);

    TControllBuilder* font(const TFont& font);
    TControllBuilder* background_color(const TColorCode color);
    TControllBuilder* width(const t_size size);
    TControllBuilder* height(const t_size size);
    TControllBuilder* display(const TDisplay display);
    TControllBuilder* enabled(const bool enable);
    TControllBuilder* multiselected(const bool selected);
    TControllBuilder* grouping(const size_t idx);
    TControllBuilder* carot();
    TControllBuilder* addCallback(const std::function<void(TOptionManager& mng)>& fn);

    std::shared_ptr<TControllBasic> build() const;

private:

    inline static const t_id getId()
    {
        static t_id_atomic id;
        return id++;
    }

    TControllBasic m_basic;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

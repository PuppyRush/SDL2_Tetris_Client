//
// Created by chaed on 18. 12. 22.
//

#ifndef CONTROLLER_MENUBUILDER_H
#define CONTROLLER_MENUBUILDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <set>
#include <functional>
#include <memory>
#include <atomic>

#include "SDLEasyGUI/Windows/GraphicInterface.h"
#include "Tetris/TOption/TOptionManager.h"

SDL_TETRIS_BEGIN

class ControllBuilder final
{
public:

    ControllBuilder(const GraphicInterface::window_ptr window, const TPoint& point, const std::string& str);
    ControllBuilder(const GraphicInterface::window_ptr window, TPoint&& point, std::string&& str);

    ControllBuilder* font(const TFont& font);
    ControllBuilder* background_color(const TColorCode color);
    ControllBuilder* width(const t_size size);
    ControllBuilder* height(const t_size size);
    ControllBuilder* display(const TDisplay display);
    ControllBuilder* enabled(const bool enable);
    ControllBuilder* multiselected(const bool selected);
    ControllBuilder* grouping(const size_t idx);
    ControllBuilder* carot();
    ControllBuilder* selected();
    ControllBuilder* addCallback(const std::function<void(TOptionManager& mng, bool isSelected)>& fn);

    std::shared_ptr<TControllBasic> build() const;

    GraphicInterface::window_ptr m_window;

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

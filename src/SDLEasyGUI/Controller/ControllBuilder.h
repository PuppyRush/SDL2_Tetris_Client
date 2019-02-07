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

    inline ControllBuilder* id(const t_id id) noexcept
    {
        m_basic.id = id;
        return this;
    }

    inline ControllBuilder* font(const TFont& font)  noexcept
    {
        m_basic.font = font;
        return this;
    }

    inline ControllBuilder* background_color(const TColorCode color) noexcept
    {
        m_basic.background_color = color;
        return this;
    }

    inline ControllBuilder* width(const t_size size) noexcept
    {
        m_basic.autoSize = false;
        m_basic.width = size;
        return this;

    }

    inline ControllBuilder* height(const t_size size) noexcept
    {
        m_basic.autoSize = false;
        m_basic.height = size;
        return this;
    }

    inline ControllBuilder* enabled(const bool enable) noexcept
    {
        m_basic.enabled = enable;
        return this;
    }

    inline ControllBuilder* multiselected(const bool selected) noexcept
    {
        m_basic.multiselected = selected;
        return this;
    }

    inline ControllBuilder* grouping(const size_t idx) noexcept
    {
        m_basic.group = idx;
        return this;
    }

    inline ControllBuilder* carot() noexcept
    {
        m_basic.carot = true;
        return this;
    }

    inline ControllBuilder* selected() noexcept
    {
        m_basic.selected = true;
        return this;
    }

    std::shared_ptr<TControllBasic> build() const;
    GraphicInterface::window_ptr m_window;

private:

    TControllBasic m_basic;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

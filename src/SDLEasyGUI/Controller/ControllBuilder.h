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


//predeclaration.
class Controll;

class ControllBuilder
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

    const GraphicInterface::window_ptr getWindow() const {
        return m_window;
    }

    const TControllBasic getBasic() const {
        return m_basic;
    }

    virtual std::shared_ptr<Controll> build() = 0;

private:

    GraphicInterface::window_ptr m_window;
    TControllBasic m_basic;

};

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

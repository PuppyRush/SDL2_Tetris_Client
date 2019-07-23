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

#include "SDL2EasyGUI/src/Windows/GraphicInterface.h"
#include "SEG_Event.h"

namespace sdleasygui {

//predeclaration.
class Control;

class ControlBuilder
{
public:

    ControlBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str);

    ControlBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str);

    virtual ~ControlBuilder() = default;

    inline ControlBuilder* id(const t_id id) noexcept
    {
        m_basic.resourceId = id;
        return this;
    }

    inline ControlBuilder* font(const SEG_TFont& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    inline ControlBuilder* fontSize(const t_size& size) noexcept
    {
        m_basic.font.size = size;
        return this;
    }

    inline ControlBuilder* fontColor(const SEG_Color& color) noexcept
    {
        m_basic.font.color = color;
        return this;
    }

    inline ControlBuilder* backgroundColor(const ColorCode color) noexcept
    {
        m_basic.backgroundColor = color;
        return this;
    }

    inline ControlBuilder* width(const t_size size) noexcept
    {
        m_basic.autoSize = false;
        m_basic.width = size;
        return this;

    }

    inline ControlBuilder* height(const t_size size) noexcept
    {
        m_basic.autoSize = false;
        m_basic.height = size;
        return this;
    }

    inline ControlBuilder* enabled(const bool enable) noexcept
    {
        m_basic.enabled = enable;
        return this;
    }

    inline ControlBuilder* multiselected(const bool selected) noexcept
    {
        m_basic.multiselected = selected;
        return this;
    }

    inline ControlBuilder* grouping(const size_t idx) noexcept
    {
        m_basic.group = idx;
        return this;
    }

    inline ControlBuilder* carot() noexcept
    {
        m_basic.carot = true;
        return this;
    }

    inline ControlBuilder* selected() noexcept
    {
        m_basic.selected = true;
        return this;
    }

    inline ControlBuilder* borderLineType(const BorderBoundaryLineType lineType)
    {
        m_basic.borderLineType = lineType;
        return this;
    }

    inline ControlBuilder* borderBoundaryType(const BorderBoundaryType type)
    {
        m_basic.borderType = type;
        return this;
    }

    inline ControlBuilder* borderColor(const SEG_Color& lineColor)
    {
        m_basic.borderColor = lineColor;
        return this;
    }

    inline ControlBuilder* borderAngle(const int borderAngle)
    {
        m_basic.borderAngle = borderAngle;
        return this;
    }

    inline ControlBuilder* borderThick(const int borderThick)
    {
        m_basic.borderThick = borderThick;
        return this;
    }

    const GraphicInterface::window_type getWindow() const
    {
        return m_window;
    }

    const TControlBasic& getBasic() const
    {
        return m_basic;
    }

    void kind(const ControlKind kind)
    {
        m_basic.kind = kind;
    }

    virtual Control* build() = 0;

private:

    GraphicInterface::window_type m_window;
    TControlBasic m_basic;

};

}

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H

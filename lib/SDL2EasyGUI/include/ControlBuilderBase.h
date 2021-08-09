//
// Created by chaed on 18. 12. 22.
//

#ifndef SDL2EASYGUI_CONTROLBUILDER_H
#define SDL2EASYGUI_CONTROLBUILDER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <set>
#include <functional>
#include <memory>
#include <atomic>

#include "SDL2EasyGUI/src/Windows/GraphicInterface.h"
#include "SEG_Event.h"

namespace seg {

//predeclaration.
class Control;

class ControlBuilderBase
{
public:

    ControlBuilderBase(const GraphicInterface::window_type window);

    virtual ~ControlBuilderBase() = default;

    inline ControlBuilderBase* kind(const ControlKind kind)
    {
        m_basic.kind = kind;
        return this;
    }

    inline const ControlData& getBasic() const
    {
        return m_basic;
    }

    virtual inline ControlBuilderBase* font(const SEG_TFont& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline ControlBuilderBase* font(SEG_TFont&& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline ControlBuilderBase* fontSize(t_size size) noexcept
    {
        m_basic.font.size = size;
        return this;
    }

    virtual inline ControlBuilderBase* fontColor(SEG_Color color) noexcept
    {
        m_basic.font.color = color;
        return this;
    }

    virtual inline ControlBuilderBase* backgroundColor(ColorCode color) noexcept
    {
        m_basic.backgroundColor = color;
        return this;
    }

    virtual inline ControlBuilderBase* enabled(bool enable) noexcept
    {
        m_basic.enabled = enable;
        return this;
    }

    virtual inline ControlBuilderBase* visible(bool visible) noexcept
    {
        m_basic.visible = visible;
        return this;
    }

    virtual Control* build() = 0;

protected:

    ControlData m_basic;

protected:

    virtual inline ControlBuilderBase* text(std::string&& str) noexcept
    {
        m_basic.text = str;
        return this;
    }

    virtual inline ControlBuilderBase* text(const std::string& str) noexcept
    {
        m_basic.text = str;
        return this;
    }

    virtual inline ControlBuilderBase* multiselected(bool selected) noexcept
    {
        m_basic.multiselected = selected;
        return this;
    }

    virtual inline ControlBuilderBase* carot() noexcept
    {
        m_basic.carot = true;
        return this;
    }

    inline GraphicInterface::window_type getWindow() const
    {
        return m_basic.window;
    }

    virtual inline ControlBuilderBase* id(t_id id) noexcept = 0;

    virtual inline ControlBuilderBase* point(SDL_Point pt) noexcept = 0;

    virtual inline ControlBuilderBase* position(SDL_Rect rect) noexcept = 0;

    virtual inline ControlBuilderBase* width(t_size size) noexcept = 0;

    virtual inline ControlBuilderBase* height(t_size size) noexcept = 0;

    virtual inline ControlBuilderBase* grouping(t_size idx) noexcept = 0;

    virtual inline ControlBuilderBase* selected() noexcept = 0;

    virtual inline ControlBuilderBase* borderLineType(BorderBoundaryLineType lineType) noexcept = 0;

    virtual inline ControlBuilderBase* borderBoundaryType(BorderBoundaryType type) noexcept = 0;

    virtual inline ControlBuilderBase* borderColor(SEG_Color lineColor) noexcept = 0;

    virtual inline ControlBuilderBase* borderAngle(int borderAngle) noexcept = 0;

    virtual inline ControlBuilderBase* borderThick(int borderThick) noexcept = 0;

};

}

#endif //SDL2EASYGUI_TMENUBUILDER_H

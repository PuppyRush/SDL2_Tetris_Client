#ifndef SDL2EASYGUI_BOXITEM_H
#define SDL2EASYGUI_BOXITEM_H

#if _MSC_VER >= 1200
#pragma once
#endif


#include <string>

#include "SDL2EasyGUI/src/Control/Control.h"

namespace seg {

class BoxItemBuilder;
//class BoxItemBasic : public Control
//{
//public:
//
//    using Base = Control;
//
//    BoxItemBasic(const BoxItemBuilder& bld)
//        : Control(bld)
//    {
//    }
//
//    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;
//
//    virtual void onDraw() override;
//
//
//    const std::string& getString() const noexcept
//    {
//        return getControlText();
//    }
//
//    virtual ~BoxItemBasic() = default;
//
//};


class BoxItem : public Control
{
public:

    using Base = Control;
    using string_type = std::string;

    BoxItem(const BoxItemBuilder& bld);

    BoxItem(BoxItemBuilder&& bld);

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override;

    virtual void onDraw() override;


    const std::string& getString() const noexcept
    {
        return getControlText();
    }

    virtual ~BoxItem() = default;

    inline t_size getIndex() const noexcept
    {
        return m_idx;
    }

    inline void setIndex(t_size i)
    {
        //caching = false;
        this->m_idx = i;
    }

    // virtual void setOriginString(std::string& _origin) = 0;

protected:
    //bool caching = false;

private:

    //BoxItem() = delete;

    t_size m_idx;
};


class BoxItemBuilder : public ControlBuilderBase
{
public:

    BoxItemBuilder() 
        :ControlBuilderBase(nullptr)
    {}

    virtual ~BoxItemBuilder() = default;

    BoxItemBuilder(const GraphicInterface::window_type window, const std::string& str)
        : ControlBuilderBase(window)
    {
        m_basic.visible = false;
        text(str);
        id(atomic::getUniqueId());
    }

    BoxItemBuilder(const GraphicInterface::window_type window, std::string&& str)
        : ControlBuilderBase(window)
    {
        m_basic.visible = false;
        text(str);
        id(atomic::getUniqueId());
    }

    BoxItemBuilder(const BoxItemBuilder& bld)
        : ControlBuilderBase(bld.getWindow())
    {
        this->m_basic.visible = bld.getBasic().visible;
        this->text(bld.getBasic().text);
        this->id(bld.getBasic().resourceId);
    }

    BoxItemBuilder(BoxItemBuilder&& bld)
        : ControlBuilderBase(bld.getWindow())
    {
        this->m_basic.visible = bld.getBasic().visible;
        this->text(bld.getBasic().text);
        this->id(bld.getBasic().resourceId);
    }

    virtual inline BoxItemBuilder* text(std::string&& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxItemBuilder* text(const std::string& str) noexcept override
    {
        m_basic.text = str;
        return this;
    }

    virtual inline BoxItemBuilder* font(const SEG_TFont& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxItemBuilder* font(SEG_TFont&& font) noexcept
    {
        m_basic.font = font;
        return this;
    }

    virtual inline BoxItemBuilder* fontSize(t_size size) noexcept
    {
        m_basic.font.size = size;
        return this;
    }

    virtual inline BoxItemBuilder* fontColor(SEG_Color color) noexcept
    {
        m_basic.font.color = color;
        return this;
    }

    virtual Control::control_ptr build() override
    {
        return new BoxItem(*this);
    }

protected:
    t_id m_id;

    virtual inline BoxItemBuilder* id(t_id id) noexcept override
    {
        m_id = atomic::getUniqueId();
        return this;
    }

private:

    virtual inline BoxItemBuilder* point(SDL_Point pt) noexcept override
    {
        return this;
    }

    virtual inline BoxItemBuilder* position(SDL_Rect rect) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* width(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* height(t_size size) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* grouping(t_size idx) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* selected() noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderLineType(BorderBoundaryLineType lineType) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderBoundaryType(BorderBoundaryType type) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderColor(SEG_Color lineColor) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderAngle(int borderAngle) noexcept
    {
        return this;
    }

    virtual inline BoxItemBuilder* borderThick(int borderThick) noexcept
    {
        return this;
    }

};

}

#endif
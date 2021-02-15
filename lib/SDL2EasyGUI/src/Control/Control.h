//
// Created by chaed on 18. 12. 26.
//

#ifndef SDL2EASYGUI_CONTROLL_H
#define SDL2EASYGUI_CONTROLL_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <atomic>

#include "../../include/SEG_Drawer.h"
#include "../../include/SEG_Struct.h"
#include "../../include/ControlBuilderBase.h"
#include "../../include/GroupControlManager.h"
#include "../Windows/EventListener.h"

namespace seg {


class ControlBuilder : public ControlBuilderBase
{
public:

    ControlBuilder(const GraphicInterface::window_type window, const SEG_Point& point, const std::string& str);

    ControlBuilder(const GraphicInterface::window_type window, SEG_Point&& point, std::string&& str);

    virtual ~ControlBuilder() = default;


    inline ControlBuilder* font(const SEG_TFont& font) noexcept override
    {
        m_basic.font = font;
        return this;
    }

    inline ControlBuilder* font(SEG_TFont&& font) noexcept override
    {
        m_basic.font = font;
        return this;

    }

    inline ControlBuilder* fontSize(t_size size) noexcept override
    {
        m_basic.font.size = size;
        return this;
    }

    inline ControlBuilder* fontColor(SEG_Color color) noexcept override
    {
        m_basic.font.color = color;
        return this;
    }

    inline ControlBuilder* backgroundColor(ColorCode color) noexcept override
    {
        m_basic.backgroundColor = color;
        return this;
    }

    inline ControlBuilder* enabled(bool enable) noexcept override
    {
        m_basic.enabled = enable;
        return this;
    }

    inline ControlBuilder* multiselected(bool selected) noexcept override
    {
        m_basic.multiselected = selected;
        return this;
    }

    inline ControlBuilder* carot() noexcept override
    {
        m_basic.carot = true;
        return this;
    }

    /// 

    inline ControlBuilder* id(t_id id) noexcept override
    {
        m_basic.resourceId = id;
        return this;
    }

    inline ControlBuilder* point(SDL_Point pt) noexcept override
    {
        m_basic.position.x = pt.x;
        m_basic.position.y = pt.y;
        return this;
    }

    inline ControlBuilder* position(SDL_Rect rect) noexcept override
    {
        m_basic.position = rect;
        return this;
    }

    inline ControlBuilder* width(t_size size) noexcept override
    {
        m_basic.autoSize = false;
        m_basic.width = size;
        return this;

    }

    inline ControlBuilder* height(t_size size) noexcept override
    {
        m_basic.autoSize = false;
        m_basic.height = size;
        return this;
    }

    inline ControlBuilder* grouping(size_t idx) noexcept override
    {
        m_basic.group = idx;
        return this;
    }

    inline ControlBuilder* selected() noexcept override
    {
        m_basic.selected = true;
        return this;
    }

    inline ControlBuilder* borderLineType(BorderBoundaryLineType lineType) noexcept override
    {
        m_basic.borderLineType = lineType;
        return this;
    }

    inline ControlBuilder* borderBoundaryType(BorderBoundaryType type) noexcept override
    {
        m_basic.borderType = type;
        return this;
    }

    inline ControlBuilder* borderColor(SEG_Color lineColor) noexcept override
    {
        m_basic.borderColor = lineColor;
        return this;
    }

    inline ControlBuilder* borderAngle(int borderAngle) noexcept override
    {
        m_basic.borderAngle = borderAngle;
        return this;
    }

    inline ControlBuilder* borderThick(int borderThick) noexcept override
    {
        m_basic.borderThick = borderThick;
        return this;
    }

    virtual Control* build() = 0;

};


class DisplayInterface;

class Control : public GraphicInterface, public EventListener
{
public:

    using renderer_type = SEG_Window::renderer_type;
    using control_ptr = Control*;

    virtual ~Control() = default;

    inline bool isActivated() const noexcept
    {
        return m_activated;
    }

    inline void setActivating(bool hit)
    {
        m_activated = hit;
    }

    inline bool wasInitailized() const noexcept
    {
        return m_isInitailize;
    }

    inline void setInitailize(bool init)
    {
        m_isInitailize = init;
    }

    inline virtual void setPosition(const SDL_Rect rect) noexcept override
    {
        setControlTextPositionX(rect.x);
        setControlTextPositionY(rect.y);
        if (getControlTextHeight() > rect.h)
            setControlTextHeight(rect.h);
        if (getControlTextWidth() > rect.w)
            setControlTextWidth(rect.w);
        GraphicInterface::setPosition(rect);
    }


    void onHit(const SEG_Point& point, const bool hit);

    void setSelected(bool selected);

    void onVirtualDraw();

    virtual bool isHit(const SEG_Point& point) const;

    virtual void resize() override
    {}

    virtual void initialize() override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void refresh() override;

    virtual void onCommonEvent(const SDL_CommonEvent* common) override
    {}

    virtual void onWindowEvent(const SDL_WindowEvent& window) override
    {}

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override;

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) override
    {}

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    {}

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override
    {}

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) override
    {}

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) override
    {}

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) override
    {}

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) override
    {}

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) override
    {}

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) override
    {}

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) override
    {}

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) override
    {}

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) override
    {}

    virtual void onQuitEvent(const SDL_QuitEvent* quit) override
    {}

    virtual void onUserEvent(const SDL_UserEvent* user) override
    {}

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) override
    {}

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) override
    {}

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) override
    {}

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) override
    {}

    virtual void onDropEvent(const SDL_DropEvent* drop) override
    {}

    virtual void onTimerEvent(const SDL_UserEvent* user) override
    {}

    virtual void onAttachFocus(const SDL_UserEvent* user) override
    {}

    virtual void onDetachFocus(const SDL_UserEvent* user) override
    {}

    virtual void onBound(const SDL_MouseMotionEvent* user) override
    {}

    virtual void onUnbound(const SDL_MouseMotionEvent* user) override
    {}
    
    //bound test
    virtual bool bound(const SDL_Event& event) override;

    //focus tset
    virtual bool focus(const SDL_Event& event) override;

    void release();

    //control text

    void setControlText(const char* ch);

    void setControlText(std::string&& str);

    void setControlText(const std::string& str);

    std::string& getControlText() noexcept;
    
    inline int getControlTextWidth() const noexcept
    {
        return m_textDrawer.getTextWidth();
    }

    inline void setControlTextWidth(int width) noexcept
    {
        m_textDrawer.setTextWidth(width);
    }

    inline int getControlTextHeight() const noexcept
    {
        return m_textDrawer.getTextHeight();
    }

    inline void setControlTextHeight(int height) noexcept
    {
        m_textDrawer.setTextHeight(height);
    }


    void setControlTextPostion(const SDL_Rect rect);

    inline SDL_Rect getControlTextPostion(const SDL_Rect rect) const noexcept;

    void setControlTextPositionX(const t_coord coord);

    inline t_coord getControlTextPositionX() const noexcept;

    void setControlTextPositionY(const t_coord coord);

    inline t_coord getControlTextPositionY() const noexcept;
        
protected:

    explicit Control(Control*);

    explicit Control(const ControlBuilder& bld);

    explicit Control(const ControlBuilderBase& bld);

    inline void stopDrawing(const bool b) noexcept
    { m_stopDraw = b; }

    inline bool isStopedDraw() const noexcept
    { return m_stopDraw; }

private:
    
    void _initializeInCtor();

private:

    bool m_stopDraw = false;
    bool m_activated = false;
    bool m_isBounded = false;
    bool m_isInitailize = false;

    drawer::TextDrawer m_textDrawer;
};

}

#endif //SDL2EASYGUI_TCONTROLL_H

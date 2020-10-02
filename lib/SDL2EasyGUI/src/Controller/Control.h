//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_CONTROLL_H
#define CONTROLLER_CONTROLL_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <atomic>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "SDL2EasyGUI/include/SEG_Struct.h"
#include "SDL2EasyGUI/include/ControlBuilder.h"
#include "SDL2EasyGUI/include/GroupControlManager.h"
#include "SDL2EasyGUI/include/EventListener.h"

namespace seg {

class DisplayInterface;

class Control : public GraphicInterface, public EventListener
{
public:

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

    inline SEG_Window::renderer_type getSDLRenderer() const noexcept
    {
        return getWindow()->getSDLRenderer();
    }

    bool isHitting(const SDL_Event& event) noexcept;

    void onHit(const SEG_Point& point, const bool hit);


    void setSelected(bool selected);

    void onVirtualDraw();

    bool isHit(const t_coord x, const t_coord y, const t_coord z = 0) const;

    virtual bool isHit(SEG_Point&& point) const;

    virtual bool isHit(const SEG_Point& point) const;

    virtual void resize() override
    {};

    virtual void initialize() override;

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void refresh() override;

    virtual void onCommonEvent(const SDL_CommonEvent* common) override
    {};

    virtual void onWindowEvent(const SDL_WindowEvent& window) override
    {};

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override;

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) override
    {};

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    {};

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override
    {};

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) override
    {};

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) override
    {};

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) override
    {};

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) override
    {};

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) override
    {};

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) override
    {};

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) override
    {};

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) override
    {};

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) override
    {};

    virtual void onQuitEvent(const SDL_QuitEvent* quit) override
    {};

    virtual void onUserEvent(const SDL_UserEvent* user) override
    {}

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) override
    {};

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) override
    {};

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) override
    {};

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) override
    {};

    virtual void onDropEvent(const SDL_DropEvent* drop) override
    {};

    virtual void onTimerEvent(const SDL_UserEvent* user) override
    {}

    virtual void onAttachFocus(const SDL_UserEvent* user) override
    {};

    virtual void onDetachFocus(const SDL_UserEvent* user) override
    {};

    virtual void onBound(const SDL_MouseMotionEvent* user) override
    {}

    virtual void onUnbound(const SDL_MouseMotionEvent* user) override
    {}
    
    virtual bool bound(const SDL_Event& event) override;

    virtual bool focus(const SDL_Event& event) override;

protected:

    explicit Control(const Control*);

    explicit Control(const ControlBuilder& bld);

    inline int getTextWidth() const noexcept
    {
        return m_textWidth;
    }


    inline void setTextWidth(int mTextWidth) noexcept
    {
        m_textWidth = mTextWidth;
    }

    inline int getTextHeight() const noexcept
    {
        return m_textHeight;
    }

    inline void setTextHeight(int mTextHeight) noexcept
    {
        m_textHeight = mTextHeight;
    }

    inline void stopDrawing(const bool b) noexcept
    { m_stopDraw = b; }

    inline bool isStopedDraw() const noexcept
    { return m_stopDraw; }

private:
    void _initializeInCtor();

private:

    int m_textWidth;
    int m_textHeight;

private:
    SDL_Rect m_positionRect;
    bool m_stopDraw = false;
    bool m_activated = false;
    bool m_isBounded = false;
};

}

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H

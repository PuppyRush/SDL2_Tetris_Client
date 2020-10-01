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

    inline bool isHitting() const noexcept
    {
        return m_isHitting;
    }

    inline void setHitting(bool hit)
    {
        Control::m_isHitting = hit;
    }

    inline SEG_Window::renderer_type getSDLRenderer() const noexcept
    {
        return getWindow()->getSDLRenderer();
    }

    bool isHitting(const SDL_Event& event) noexcept;
    /*{ return m_isHitting; }*/

    void onHit(const SEG_Point& point, const bool hit);

    bool isBounded(const SDL_Event& event);

    void setSelected(bool selected);

    void onVirtualDraw();

    bool isHit(const t_coord x, const t_coord y, const t_coord z = 0) const;

    virtual bool isHit(const SEG_Point& point) const;

    virtual void resize() override
    {};

    virtual void initialize() override;

    virtual void onDraw();

    virtual void onDrawBackground();

    virtual void refresh();

    virtual void onCommonEvent(const SDL_CommonEvent* common)
    {};

    virtual void onWindowEvent(const SDL_WindowEvent& window)
    {};

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key);

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit)
    {};

    virtual void onTextInputEvent(const SDL_TextInputEvent* text);

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
    {
    };

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button)
    {}

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
    {};

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis)
    {};

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball)
    {};

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat)
    {};

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton)
    {};

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice)
    {};

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis)
    {};

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton)
    {};

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice)
    {};

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice)
    {};

    virtual void onQuitEvent(const SDL_QuitEvent* quit)
    {};

    virtual void onUserEvent(const SDL_UserEvent* user)
    {}

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm)
    {};

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger)
    {};

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture)
    {};

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture)
    {};

    virtual void onDropEvent(const SDL_DropEvent* drop)
    {};

    virtual void onTimerEvent(const SDL_UserEvent* user)
    {}

    virtual void onAttachFocus()
    {};

    virtual void onDetachFocus()
    {};

protected:

    explicit Control(const Control*);

    explicit Control(const ControlBuilder& bld);

    void drawBackground(const SDL_Rect rect, const SEG_Color color);

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
    bool m_isHitting = false;
    bool m_isBounded = false;
};

}

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H

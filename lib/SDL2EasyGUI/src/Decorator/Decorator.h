//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2_TETRIS_CLIENT_DECORATOR_H
#define SDL2_TETRIS_CLIENT_DECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "../Controller/Control.h"

namespace sdleasygui {

class Decorator : public Control
{
public:
    explicit Decorator(Control*);

    virtual void onDraw() override;

    virtual void onDrawBackground() override;

    virtual void refresh() override;

    virtual void resize() override;

    virtual void initialize() override
    {}

    inline auto getComponent()
    { return m_graphic; }

protected:

    virtual void onCommonEvent(const SDL_CommonEvent* common) override final
    { m_graphic->onCommonEvent(common); };

    virtual void onWindowEvent(const SDL_WindowEvent& window) override final
    { m_graphic->onWindowEvent(window); };

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override final
    { m_graphic->onKeyboardEvent(key); }

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) override final
    { m_graphic->onTextEditingEvent(edit); };

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override final
    {
        m_graphic->onTextInputEvent(text);
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override final
    {
        m_graphic->onMouseMotionEvent(motion);
    };

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override final
    { m_graphic->onMouseButtonEvent(button); }

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override final
    { m_graphic->onMouseWheelEvent(wheel); };

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) override final
    { m_graphic->onJoyAxisEvent(jaxis); };

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) override final
    { m_graphic->onJoyBallEvent(jball); };

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) override final
    { m_graphic->onJoyHatEvent(jhat); };

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) override final
    { m_graphic->onJoyButtonEvent(jbutton); };

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) override final
    { m_graphic->onJoyDeviceEvent(jdevice); };

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) override final
    { m_graphic->onControllerAxisEvent(caxis); };

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) override final
    { m_graphic->onControllerButtonEvent(cbutton); };

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) override final
    { m_graphic->onControllerDeviceEvent(cdevice); };

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) override final
    { m_graphic->onAudioDeviceEvent(adevice); };

    virtual void onQuitEvent(const SDL_QuitEvent* quit) override final
    { m_graphic->onQuitEvent(quit); };

    virtual void onUserEvent(const SDL_UserEvent* user) override final
    { m_graphic->onUserEvent(user); }

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) override final
    { m_graphic->onSysWMEvent(syswm); };

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) override final
    { m_graphic->onTouchFingerEvent(tfinger); };

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) override final
    { m_graphic->onMultiGestureEvent(mgesture); };

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) override final
    { m_graphic->onDollarGestureEvent(dgesture); };

    virtual void onDropEvent(const SDL_DropEvent* drop) override final
    { m_graphic->onDropEvent(drop); };

    virtual void onTimerEvent(const SDL_UserEvent* user) override final
    { m_graphic->onTimerEvent(user); }

    virtual void onAttachFocus() override final
    { m_graphic->onAttachFocus(); };

    virtual void onDetachFocus() override final
    { m_graphic->onDetachFocus(); };

private:

    Control* m_graphic;

};

}

#endif //SDL2_TETRIS_CLIENT_DECORATOR_H

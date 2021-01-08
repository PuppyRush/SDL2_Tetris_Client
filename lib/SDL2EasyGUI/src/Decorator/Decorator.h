//
// Created by chaed on 19. 7. 15.
//

#ifndef SDL2_TETRIS_CLIENT_DECORATOR_H
#define SDL2_TETRIS_CLIENT_DECORATOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <unordered_map>

#include "../Control/Control.h"

namespace seg {

template<class T>
class Decorator : public Control
{
public:

    using DecoratorBase = T;

    Decorator(DecoratorBase* gi)
            : m_graphic(gi), Control(gi)
    {

    }

    virtual ~Decorator()
    {
    }

    void onDraw()
    {
        m_graphic->onDraw();
    }

    void onDrawBackground()
    {
        m_graphic->onDrawBackground();
    }

    void refresh()
    {
        m_graphic->refresh();
    }

    void resize()
    {
        m_graphic->resize();
    }

    virtual void initialize() override
    {}

    inline auto getComponent()
    { return m_graphic; }


    virtual void onCommonEvent(const SDL_CommonEvent* common) override
    { m_graphic->onCommonEvent(common); };

    virtual void onWindowEvent(const SDL_WindowEvent& window) override
    { m_graphic->onWindowEvent(window); };

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) override
    { m_graphic->onKeyboardEvent(key); }

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) override
    { m_graphic->onTextEditingEvent(edit); };

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) override
    { m_graphic->onTextInputEvent(text); }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    { m_graphic->onMouseMotionEvent(motion); };

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) override
    { m_graphic->onMouseButtonEvent(button); }

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) override
    { m_graphic->onMouseWheelEvent(wheel); };

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) override
    { m_graphic->onJoyAxisEvent(jaxis); };

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) override
    { m_graphic->onJoyBallEvent(jball); };

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) override
    { m_graphic->onJoyHatEvent(jhat); };

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) override
    { m_graphic->onJoyButtonEvent(jbutton); };

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) override
    { m_graphic->onJoyDeviceEvent(jdevice); };

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) override
    { m_graphic->onControllerAxisEvent(caxis); };

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) override
    { m_graphic->onControllerButtonEvent(cbutton); };

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) override
    { m_graphic->onControllerDeviceEvent(cdevice); };

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) override
    { m_graphic->onAudioDeviceEvent(adevice); };

    virtual void onQuitEvent(const SDL_QuitEvent* quit) override
    { m_graphic->onQuitEvent(quit); };

    virtual void onUserEvent(const SDL_UserEvent* user) override
    { m_graphic->onUserEvent(user); }

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) override
    { m_graphic->onSysWMEvent(syswm); };

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) override
    { m_graphic->onTouchFingerEvent(tfinger); };

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) override
    { m_graphic->onMultiGestureEvent(mgesture); };

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) override
    { m_graphic->onDollarGestureEvent(dgesture); };

    virtual void onDropEvent(const SDL_DropEvent* drop) override
    { m_graphic->onDropEvent(drop); };

    virtual void onTimerEvent(const SDL_UserEvent* user) override
    { m_graphic->onTimerEvent(user); }

    virtual void onAttachFocus(const SDL_UserEvent* user) override
    { m_graphic->onAttachFocus(user); };

    virtual void onDetachFocus(const SDL_UserEvent* user) override
    { m_graphic->onDetachFocus(user); };

    virtual void onBound(const SDL_MouseMotionEvent* user) override
    { m_graphic->onBound(user); }

    virtual void onUnbound(const SDL_MouseMotionEvent* user) override
    { m_graphic->onUnbound(user); }

    virtual bool bound(const SDL_Event& event) override
    { return m_graphic->bound(event); }

    virtual bool focus(const SDL_Event& event) override
    { return m_graphic->focus(event); }


private:

    T* m_graphic;

    
};

template <class T, class Ctl>
class DecoratorMap
{
public:
    static T* get_decorator(Ctl* ctl);

    static std::unordered_map<Ctl*, T*> m_decoratorMap;

    ~DecoratorMap()
    {
        for (auto pair : DecoratorMap<T, Ctl>::m_decoratorMap)
        {
            delete pair.second;
        }

    }
};

template <class T, class Ctl>
std::unordered_map<Ctl*, T*> DecoratorMap<T,Ctl>::m_decoratorMap;

template <class T, class Ctl>
T* DecoratorMap<T, Ctl>::get_decorator(Ctl* ctl)
{
    if (m_decoratorMap.find(ctl) == m_decoratorMap.end())
    {
        auto dec = new T{ctl};
        m_decoratorMap.insert(std::make_pair(ctl, dec));
    }
    return m_decoratorMap.at(ctl);
}

}

#endif //SDL2_TETRIS_CLIENT_DECORATOR_H

//
// Created by chaed on 19. 8. 8..
//

#ifndef SDL2_TETRIS_CLIENT_SEG_DEBUG_H
#define SDL2_TETRIS_CLIENT_SEG_DEBUG_H


#if _MSC_VER >= 1200
#pragma once
#endif

#define __NOOP ;

#include <string>

namespace seg {
namespace debug {

class SEG_Debug
{
public:
    enum class debug_level
    {
        lv1,
        lv2,
        lv3,
        lv4,
        lv5
    };

    static void setDebugLevel(const debug_level lv)
    { m_debugLevel = lv; }

    static SEG_Debug& getInstance()
    {
        static SEG_Debug debug;
        return debug;
    }

    void SEG_Print(const char* str)
    {
#ifdef _DEBUG
        printf("%s", str);
#else
    __NOOP
#endif
    }

    void SEG_Print(const std::string& str)
    {
#ifdef _DEBUG
        printf("%s", str.c_str());
#else
        __NOOP
#endif
    }

protected:
  /*  //SDL Events
    virtual void onCommonEvent(const SDL_CommonEvent* common)
    {

    }

    virtual void onWindowEvent(const SDL_WindowEvent& window)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onTextInputEvent(const SDL_TextInputEvent* text)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button)
    {
        switch (m_debugLevel)
        {
            case debug_level::lv1:
            case debug_level::lv2:
            case debug_level::lv3:
            case debug_level::lv4:
            case debug_level::lv5:

                break;
            default:
                break;
        }
    }

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel)
    {}

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis)
    {}

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball)
    {}

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat)
    {}

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton)
    {}

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice)
    {}

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis)
    {}

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton)
    {}

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice)
    {}

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice)
    {}

    virtual void onQuitEvent(const SDL_QuitEvent* quit)
    {}

    virtual void onUserEvent(const SDL_UserEvent* user)
    {}

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm)
    {}

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger)
    {}

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture)
    {}

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture)
    {}

    virtual void onDropEvent(const SDL_DropEvent* drop)
    {}

    virtual void onTimerEvent(const SDL_UserEvent* user)
    {}

    //SEG Events
    virtual void onAttachFocus()
    {}

    virtual void onDetachFocus()
    {}*/

private:
    SEG_Debug() = default;

    static debug_level m_debugLevel;
};

SEG_Debug::debug_level SEG_Debug::m_debugLevel = debug_level::lv1;

}
}

#endif //SDL2_TETRIS_CLIENT_SEG_DEBUG_H

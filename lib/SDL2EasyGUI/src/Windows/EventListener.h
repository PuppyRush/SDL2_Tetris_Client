//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTLISTENER_H
#define TETRIS_FIGURE_CLASS_EVENTLISTENER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <SDL2/SDL.h>
#include "SDL2EasyGUI/include/EventQueue.h"
#include "SDL2EasyGUI/include/SEG_Property.h"
#include "GameInterface/include/Logger.h"

namespace seg {

class EventListener
{

public:

    using queue_type = EventQueue<SDL_Event>;
    using data_type = queue_type::data_type;

    virtual ~EventListener() = default;

    virtual void onEvent(const SDL_Event& event)
    {
        using namespace game_interface::logger;
        
        switch (event.type) {
            case SDL_WINDOWEVENT   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_WINDOWEVENT", Logger::logger_level::Debug);
                onWindowEvent(event.window);
                break;
            case SDL_SYSWMEVENT    :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_SYSWMEVENT", Logger::logger_level::Debug);
                onSysWMEvent(&event.syswm);
                break;
            case SDL_KEYDOWN       :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_KEYDOWN", Logger::logger_level::Debug);
                onKeyboardEvent(&event.key);
                break;
            case SDL_KEYUP:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_KEYUP", Logger::logger_level::Debug);
                onKeyboardEvent(&event.key);
                break;
            case SDL_TEXTEDITING   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_TEXTEDITING", Logger::logger_level::Debug);
                onTextEditingEvent(&event.edit);
                break;
            case SDL_TEXTINPUT:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_TEXTINPUT", Logger::logger_level::Debug);
                onTextInputEvent(&event.text);
                break;
            case SDL_KEYMAPCHANGED :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_KEYMAPCHANGED", Logger::logger_level::Debug);
                break;
            case SDL_MOUSEMOTION   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_MOUSEMOTION", Logger::logger_level::Debug);
                onMouseMotionEvent(&event.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_MOUSEBUTTONDOWN", Logger::logger_level::Debug);
                onMouseButtonEvent(&event.button);
                break;
            case SDL_MOUSEBUTTONUP :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_MOUSEBUTTONUP", Logger::logger_level::Debug);
                //onMouseButtonEvent(&event.button);
                break;
            case SDL_MOUSEWHEEL    :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_MOUSEWHEEL", Logger::logger_level::Debug);
                onMouseWheelEvent(&event.wheel);
                break;
            case SDL_JOYBUTTONDOWN   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYBUTTONDOWN", Logger::logger_level::Debug);
                onJoyButtonEvent(&event.jbutton);
                break;
            case SDL_JOYBUTTONUP     :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYBUTTONUP", Logger::logger_level::Debug);
                onJoyButtonEvent(&event.jbutton);
                break;
            case SDL_JOYBALLMOTION   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYBALLMOTION", Logger::logger_level::Debug);
                onJoyBallEvent(&event.jball);
                break;
            case SDL_JOYHATMOTION    :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYHATMOTION", Logger::logger_level::Debug);
                onJoyHatEvent(&event.jhat);
                break;
            case SDL_JOYAXISMOTION   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYAXISMOTION", Logger::logger_level::Debug);
                onJoyAxisEvent(&event.jaxis);
                break;
            case SDL_JOYDEVICEADDED  :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYDEVICEADDED", Logger::logger_level::Debug);
                onJoyDeviceEvent(&event.jdevice);
                break;
            case SDL_JOYDEVICEREMOVED:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_JOYDEVICEREMOVED", Logger::logger_level::Debug);
                onJoyDeviceEvent(&event.jdevice);
                break;
            case SDL_CONTROLLERAXISMOTION:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERAXISMOTION", Logger::logger_level::Debug);
                onControllerAxisEvent(&event.caxis);
                break;
            case SDL_CONTROLLERBUTTONDOWN :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERBUTTONDOWN", Logger::logger_level::Debug);
                onControllerButtonEvent(&event.cbutton);
                break;
            case SDL_CONTROLLERBUTTONUP   :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERBUTTONUP", Logger::logger_level::Debug);
                onControllerButtonEvent(&event.cbutton);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERDEVICEREMOVED", Logger::logger_level::Debug);
                onControllerDeviceEvent(&event.cdevice);
                break;
            case SDL_CONTROLLERDEVICEREMAPPED:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERDEVICEREMAPPED", Logger::logger_level::Debug);
                onControllerDeviceEvent(&event.cdevice);
                break;
            case SDL_CONTROLLERDEVICEADDED :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLERDEVICEADDED", Logger::logger_level::Debug);
                onControllerDeviceEvent(&event.cdevice);
                break;
            case SDL_FINGERDOWN:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_FINGERDOWN", Logger::logger_level::Debug);
                break;
            case SDL_FINGERUP:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_FINGERUP", Logger::logger_level::Debug);
                break;
            case SDL_FINGERMOTION:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_FINGERMOTION", Logger::logger_level::Debug);
                break;
            case SDL_DOLLARGESTURE:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DOLLARGESTURE", Logger::logger_level::Debug);
                break;
            case SDL_DOLLARRECORD:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DOLLARRECORD", Logger::logger_level::Debug);
                break;
            case SDL_MULTIGESTURE:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_MULTIGESTURE", Logger::logger_level::Debug);
                break;
            case SDL_CLIPBOARDUPDATE:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CLIPBOARDUPDATE", Logger::logger_level::Debug);
                break;
            case SDL_DROPFILE:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DROPFILE", Logger::logger_level::Debug);
                break;
            case SDL_DROPBEGIN:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DROPBEGIN", Logger::logger_level::Debug);
                break;
            case SDL_DROPCOMPLETE:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DROPCOMPLETE", Logger::logger_level::Debug);
                break;
            case SDL_DROPTEXT:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DROPTEXT", Logger::logger_level::Debug);
                break;
            case SDL_AUDIODEVICEADDED:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_AUDIODEVICEADDED", Logger::logger_level::Debug);
                break;
            case SDL_AUDIODEVICEREMOVED:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_AUDIODEVICEREMOVED", Logger::logger_level::Debug);
                break;
            case SDL_RENDER_TARGETS_RESET:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_RENDER_TARGETS_RESET", Logger::logger_level::Debug);
                break;
            case SDL_RENDER_DEVICE_RESET :
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_RENDER_DEVICE_RESET", Logger::logger_level::Debug);
                break;
            case SEG_DRAW:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_DRAW", Logger::logger_level::Debug);
                onUserEvent(&event.user);
                break;
            case SDL_USEREVENT:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : default(SDL_USEREVENT)", Logger::logger_level::Debug);
                onUserEvent(&event.user);
                break;
            case SEG_CONTROLLER:
                switch (event.user.code)
                {
                case SEG_ATTACH_FOCUS:
                    Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLER, code : SEG_ATTACH_FOCUS", Logger::logger_level::Debug);
                    onAttachFocus(&event.user);
                    break;
                case SEG_DETACH_FOCUS:
                    Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLER, code : SEG_DETACH_FOCUS", Logger::logger_level::Debug);
                    onDetachFocus(&event.user);
                    break;
                case SEG_BOUND:
                    Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLER, code : SEG_BOUND", Logger::logger_level::Debug);
                    onBound(&event.motion);
                    break;
                case SEG_UNBOUND:
                    Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLER, code : SEG_UNBOUND", Logger::logger_level::Debug);
                    onUnbound(&event.motion);
                    break;
                default:
                    Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_CONTROLLER, default", Logger::logger_level::Debug);
                    onUserEvent(&event.user);
                }
                break;
            case SEG_TIMER_EVENT:
                Logger::getInstance().printLog("EventListener::onEvent, event_type : SDL_TIMER_EVENT", Logger::logger_level::Debug);
                onTimerEvent(&event.user);
                break;
            default:;

        }
    }

    //SDL Events
    virtual void onCommonEvent(const SDL_CommonEvent* common) = 0;

    virtual void onWindowEvent(const SDL_WindowEvent& window) = 0;

    virtual void onKeyboardEvent(const SDL_KeyboardEvent* key) = 0;

    virtual void onTextEditingEvent(const SDL_TextEditingEvent* edit) = 0;

    virtual void onTextInputEvent(const SDL_TextInputEvent* text) = 0;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) = 0;

    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent* button) = 0;

    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent* wheel) = 0;

    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent* jaxis) = 0;

    virtual void onJoyBallEvent(const SDL_JoyBallEvent* jball) = 0;

    virtual void onJoyHatEvent(const SDL_JoyHatEvent* jhat) = 0;

    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent* jbutton) = 0;

    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent* jdevice) = 0;

    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent* caxis) = 0;

    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent* cbutton) = 0;

    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent* cdevice) = 0;

    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent* adevice) = 0;

    virtual void onQuitEvent(const SDL_QuitEvent* quit) = 0;

    virtual void onUserEvent(const SDL_UserEvent* user) = 0;

    virtual void onSysWMEvent(const SDL_SysWMEvent* syswm) = 0;

    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent* tfinger) = 0;

    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent* mgesture) = 0;

    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent* dgesture) = 0;

    virtual void onDropEvent(const SDL_DropEvent* drop) = 0;

    virtual void onTimerEvent(const SDL_UserEvent* user) = 0;

    //SEG Events
    virtual void onAttachFocus(const SDL_UserEvent* user) = 0;

    virtual void onDetachFocus(const SDL_UserEvent* user) = 0;

    virtual void onBound(const SDL_MouseMotionEvent* user) = 0;

    virtual void onUnbound(const SDL_MouseMotionEvent* user) = 0;

    //Event Queue
    void pushEvent(const data_type event)
    { m_eventDelivery.pushEvent(event); }

    const data_type popEvent()
    { return m_eventDelivery.popEvent(); }


protected:
    EventQueue<SDL_Event> m_eventDelivery;

    EventListener() = default;

private:

};

}

#endif //TETRIS_FIGURE_CLASS_EVENTLISTENER_H


#ifndef GUI_DISPLAYINTERFACE_H
#define GUI_DISPLAYINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>
#include <thread>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

#include "Window.h"
#include "EventListener.h"
#include "EventQueue.h"
#include "SDLEasyGUI/Controller/ControllBuilder.h"
#include "SDLEasyGUI/Controller/Controll.h"

class DisplayInterface : public GraphicInterface
{
public:

    using BTN_CLICK = std::function<void(void)>;

    void addControll(const std::shared_ptr<Controll> ctl);
    bool clickedMenuEvent(const TPoint &point);

    t_res modal();
    void modaless();

    void show() { getWindow()->show(); }
    void hidden() { getWindow()->hidden(); }
    t_res initialize();
    void pushDrawDisplayEvent();
    virtual void onDraw();

    inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path; }
    inline void setRun(const bool run) { m_run = run; }
    inline void setStopDraw(const bool set) { m_stopDraw = set; }

    inline const t_display getDisplay() const noexcept {   return m_display;  }
    inline const TLocalMode getMode() const noexcept {  return m_mode;  }
    inline const bool getRun() const noexcept { return m_run; }
    inline const bool getSetDraw() const noexcept { return m_stopDraw; }
    inline const t_id getID() const noexcept { return m_id; }
    inline const t_id getWindowID() const noexcept { return getWindow()->getWindowID(); }

    virtual ~DisplayInterface();

protected:
    DisplayInterface();

    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept {
        return getWindow()->getSDLWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept {
        return getWindow()->getSDLRenderer();
    }

    virtual void registerEvent() {}
    virtual void event_buttonClick(const t_res, const BTN_CLICK callback_fn);

    virtual void onPreDraw();
    virtual void onPreInitialize();
    virtual void onCreate();
    virtual void onClose();
    virtual void onOK();
    virtual void onNO();
    virtual void onCancel();
    virtual void onDestroy();

    //events
    virtual void onCommonEvent (const SDL_CommonEvent* common)  {};
    virtual void onWindowEvent (const SDL_WindowEvent& window) override;
    virtual void onKeyboardEvent (const SDL_KeyboardEvent* key)  {};
    virtual void onTextEditingEvent (const SDL_TextEditingEvent* edit)  {};
    virtual void onTextInputEvent (const SDL_TextInputEvent* text)  {};
    virtual void onMouseMotionEvent (const SDL_MouseMotionEvent* motion)  {};
    virtual void onMouseButtonEvent (const SDL_MouseButtonEvent* button);
    virtual void onMouseWheelEvent (const SDL_MouseWheelEvent* wheel)  {};
    virtual void onJoyAxisEvent (const SDL_JoyAxisEvent* jaxis)  {};
    virtual void onJoyBallEvent (const SDL_JoyBallEvent*jball)  {};
    virtual void onJoyHatEvent (const SDL_JoyHatEvent* jhat)  {};
    virtual void onJoyButtonEvent (const SDL_JoyButtonEvent* jbutton)  {};
    virtual void onJoyDeviceEvent (const SDL_JoyDeviceEvent* jdevice)  {};
    virtual void onControllerAxisEvent (const SDL_ControllerAxisEvent* caxis)  {};
    virtual void onControllerButtonEvent (const SDL_ControllerButtonEvent* cbutton)  {};
    virtual void onControllerDeviceEvent (const SDL_ControllerDeviceEvent* cdevice)  {};
    virtual void onAudioDeviceEvent (const SDL_AudioDeviceEvent* adevice)  {};
    virtual void onQuitEvent (const SDL_QuitEvent *quit)  {};
    virtual void onUserEvent (const SDL_UserEvent* user) ;
    virtual void onSysWMEvent (const SDL_SysWMEvent* syswm)  {};
    virtual void onTouchFingerEvent (const SDL_TouchFingerEvent* tfinger)  {};
    virtual void onMultiGestureEvent (const SDL_MultiGestureEvent* mgesture)  {};
    virtual void onDollarGestureEvent (const SDL_DollarGestureEvent* dgesture)  {};
    virtual void onDropEvent (const SDL_DropEvent* drop)  {};

    Controll::controll_ptr getControll(const t_res);

    t_display m_display;
    TLocalMode m_mode;

    std::unordered_map<t_res, std::function<void(void)>> m_callback_no_param;
    std::unordered_map<t_res, std::function<void(const void*)>> m_callback_one_param;
    std::unordered_map<t_res, std::function<void(const void*,const void*)>> m_callback_two_param;

private:

    void _release();
    void _run();

    void onDrawMenus();
    virtual void onTimer(){}
    virtual bool validId(const t_id id) override final;

    std::vector<std::shared_ptr<Controll>> m_menus;

    std::string m_backgroundImgPath;
    t_id m_id;
    bool m_stopDraw = false;
    std::thread m_thread;
    std::atomic_bool m_run = true;

};

#endif
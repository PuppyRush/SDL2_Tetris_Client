
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
#include <unordered_map>
#include <mutex>
#include <condition_variable>

#include "Window.h"
#include "Tetris/Common/Resource.h"
#include "SDLEasyGUI/Controller/ControllBuilder.h"
#include "SDLEasyGUI/Controller/Controll.h"

SDL_TETRIS_BEGIN

class DisplayInterface : public GraphicInterface
{

public:

    using BTN_CLICK = std::function<void(void)>;

    void addControll(const std::shared_ptr<Controll> ctl);
    bool clickedMenuEvent(const TPoint &point);

    void show() { getWindow()->show(); }
    void hidden() { getWindow()->hidden(); }
    resource run();


    inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path; }
    inline void setRun(const bool run) { m_run = run; }
    inline void setStopDraw(const bool set) { m_stopDraw = set; }

    inline const TDisplay getDisplay() const noexcept {   return m_display;  }
    inline const TLocalMode getMode() const noexcept {  return m_mode;  }
    inline const bool getRun() const noexcept { return m_run; }
    inline const bool getSetDraw() const noexcept { return m_stopDraw; }
    inline const t_id getID() const noexcept { return m_id; }

    virtual ~DisplayInterface();

protected:
    DisplayInterface();

    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept {
        return getWindow()->getSDLWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept {
        return getWindow()->getSDLRenderer();
    }

    virtual void registerEvent() = 0;
    virtual void event_buttonClick(const resource, const BTN_CLICK callback_fn);
    virtual void event(const SDL_Event *event);

    virtual void onPreInitialize();
    virtual void onCreate();
    virtual void onWindowEvent(const SDL_Event *event);
    virtual void onClose();
    virtual void onOK();
    virtual void onNO();
    virtual void onCancel();
    virtual void onDestroy();
    virtual void onDraw() = 0;
    void refresh();

    Controll::controll_ptr getControll(const resource);

    TDisplay m_display;
    TLocalMode m_mode;

    std::unordered_map<resource, std::function<void(void)>> m_callback_no_param;
    std::unordered_map<resource, std::function<void(const void*)>> m_callback_one_param;
    std::unordered_map<resource, std::function<void(const void*,const void*)>> m_callback_two_param;

private:

    void _release();
    void _initializing();
    void _onDrawMenus();
    virtual void timer() = 0;

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept { return getWindow()->getSDLEvent(); }

    std::condition_variable m_cv;
    std::mutex m_mutex;

    std::vector<std::shared_ptr<Controll>> m_menus;

    std::string m_backgroundImgPath;
    t_id m_id;
    bool m_stopDraw = false;
    std::atomic_bool m_run = true;

};

SDL_TETRIS_END

#endif
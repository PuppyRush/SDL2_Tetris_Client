
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
#include "SDLEasyGUI/Controller/ControllBuilder.h"
#include "SDLEasyGUI/Controller/Controll.h"

SDL_TETRIS_BEGIN

class DisplayInterface : public GraphicInterface{
public:
    //imple 'enum class' at child class.
    enum class UIResource : t_type;

    inline bool operator==(const DisplayInterface *dp) {
        return this->m_display == dp->m_display;
    }

    void addControll(const std::shared_ptr<Controll> ctl);
    bool clickedMenuEvent(const TPoint &point);

    void show(){getWindow()->show();}
    void hidden(){getWindow()->hidden();}

    void run();
    void setDisplay(const TDisplay dp);

    inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path; }
    inline void setGoBack(const bool end) { m_goBack = end; }
    inline void setRun(const bool run) { m_run = run; }
    inline void setStopDraw(const bool set) { m_stopDraw = set; }

    inline const bool getGoBack() const noexcept { return m_goBack; }
    inline const bool getRun() const noexcept { return m_run; }
    inline const bool getSetDraw() const noexcept { return m_stopDraw; }
    inline const TDisplay getDisplay() const noexcept { return m_display; }

    virtual ~DisplayInterface();
    virtual void _event(const SDL_Event *event);
    virtual bool onClickedBack(const TDisplay disply) = 0;

protected:
    DisplayInterface();
    void _refresh();

    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept {
        return getWindow()->getSDLWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept {
        return getWindow()->getSDLRenderer();
    }

    virtual void onPreInitialize();
    virtual void onCreate();
    virtual void onWindowEvent(const SDL_Event *event);
    virtual void onClose();
    virtual void onDestroy();

    virtual void onDraw() = 0;

private:

    void _release();
    void _initializing();
    void _onDrawMenus();
    virtual void _timer() = 0;

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept { return getWindow()->getSDLEvent(); }

    std::vector<std::shared_ptr<Controll>> m_menus;
    std::string m_backgroundImgPath;
    bool m_stopDraw = false;
    bool m_goBack;
    std::atomic_bool m_run = true;
    std::mutex m;
    std::condition_variable cv;
private:
    TDisplay m_display;
};

SDL_TETRIS_END

#endif
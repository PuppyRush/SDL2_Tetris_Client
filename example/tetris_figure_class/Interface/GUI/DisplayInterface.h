
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

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "Window.h"
#include "Common/THeader.h"
#include "Interface/Controller/ControllBuilder.h"
#include "Interface/Controller/Controll.h"

SDL_TETRIS_BEGIN

class DisplayInterface {
public:
    //imple 'enum class' at child class.
    enum class UIResource : t_type;

    inline bool operator==(const DisplayInterface *dp) {
        return this->m_display == dp->m_display;
    }

    void addMenu(const std::shared_ptr<Controll> ctl);
    bool clickedMenuEvent(const TPoint &point);

    void show(){m_window->show();}
    void hidden(){m_window->hidden();}

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
    virtual bool clickedBack(const TDisplay disply) = 0;

protected:
    DisplayInterface();
    void _refresh();

    inline std::shared_ptr<SDL_Window> getSDLWindow() const noexcept {
        return m_window->getWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept {
        return m_window->getRenderer();
    }

    inline std::shared_ptr<Window> getWindow() const noexcept { return m_window; }

    virtual void _preInitialize() = 0;
    virtual void _draw() = 0;

private:

    void _initializing();
    void _drawMenus();

    void _release();

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept { return m_window->getSDLEvent(); }

    virtual void _timer() = 0;

    std::vector<std::shared_ptr<Controll>> m_menus;
    std::string m_backgroundImgPath;
    std::shared_ptr<Window> m_window;

    int m_frameTime = 0;
    bool m_stopDraw = false;
    bool m_goBack;
    std::atomic_bool m_run = true;

private:
    TDisplay m_display;
};

SDL_TETRIS_END

#endif
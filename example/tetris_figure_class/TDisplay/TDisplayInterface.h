#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "TWindow.h"
#include "../Common/THeader.h"
#include "TMenuBuilder.h"

SDL_TETRIS_BEGIN

class TDisplayInterface
{
public:
	//imple 'enum class' at child class.
    enum class UIResource : t_type;

    inline bool operator==(const TDisplayInterface* dp)
	{
		return this->m_display == dp->m_display;
	}

	void addMenu(const TMenuBuilder& bld);
    bool clickedMenuEvent(const TPoint& point);

	void erase();
	void show();
	void hide();

	inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path;}
	inline void setGoBack(const bool end) { m_goBack = end;}
	inline void setDisplay(const TDisplay dp) { m_display = dp;}
	inline void setRun(const bool run) { m_run = run;}

	inline const bool getGoBack() const noexcept{ return m_goBack;}
	inline const bool getRun() const noexcept{ return m_run;}
	inline const TDisplay getDisplay() const noexcept{ return m_display;}


    virtual ~TDisplayInterface();
	virtual bool clickedBack(const TDisplay disply) = 0;

protected:
    TDisplayInterface();

    inline std::shared_ptr<SDL_Window> getWindow() const noexcept
    {
        return m_window->getWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept
    {
        return m_window->getRenderer();
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept
    {
        return m_window->getSDLEvent();
    }

private:

	//Draw Menus.
	void _initialize();
	virtual void _event(const SDL_Event* event) =0;
	virtual void _timer() =0;
	virtual void _draw() =0;
	void _release();

	std::vector<std::shared_ptr<TMenu>> m_menus;
	std::string m_backgroundImgPath;
    std::shared_ptr<TWindow> m_window;

	bool m_goBack;
	bool m_canGoOtherDisplay;
	std::atomic_bool m_run = true;
	TDisplay m_display;
};



SDL_TETRIS_END
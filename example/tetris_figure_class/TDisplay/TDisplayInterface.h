#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "../Common/THeader.h"
#include "TMenuBuilder.h"



SDL_TETRIS_BEGIN

class TDisplayInterface
{
public:
	//imple 'enum class' at child class.
    enum class UIResource : t_type;

    virtual ~TDisplayInterface();

    inline bool operator==(const TDisplayInterface* dp)
	{
		return this->m_display == dp->m_display;
	}

	void addMenu(const TMenuBuilder& bld);
	void draw();
	void erase();
	void show();
	void hide();

	inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path;}
	inline void setGoBack(const bool end) { m_goBack = end;}
	inline void setDisplay(const TDisplay dp) { m_display = dp;}

	inline const bool getGoBack() const noexcept{ return m_goBack;}
	inline const TDisplay getDisplay() const noexcept{ return m_display;}
    inline const size_t getDisplayWidth() const noexcept { return m_windowWidth; }
    inline const size_t getDisplayHeight() const noexcept{ return m_windowHeight; }

	virtual bool clickedBack() = 0;

protected:
    TDisplayInterface();

    inline std::shared_ptr<SDL_Window> getWindow() const noexcept
    {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept
    {
        return m_renderer;
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept
    {
        return m_event;
    }

private:

	//Draw Menus.
	void Initialize();

	virtual void _setDisplay() =0;

	std::vector<std::shared_ptr<TMenu>> m_menus;
	std::shared_ptr<SDL_Window> m_window;
	std::shared_ptr<SDL_Renderer> m_renderer;
	std::shared_ptr<SDL_Event> m_event;
	std::string m_backgroundImgPath;
	const tetris::t_size m_windowWidth;
	const tetris::t_size m_windowHeight;
	bool m_goBack;
	TDisplay m_display;
};



SDL_TETRIS_END
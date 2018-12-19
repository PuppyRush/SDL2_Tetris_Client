#pragma once

#include <string>
#include <vector>
#include <memory>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

#include "../Common/TType.h"
#include "../Common/TProperty.h"
#include "../Common/TDefine.h"

SDL_TETRIS_BEGIN

typedef struct Menu
{
	TPoint point;
	TFont font;
	TColor color;
	std::string menustring;
};

class TDisplayInterface
{
public:
    enum class UIResource : t_type;

    virtual ~TDisplayInterface();
	virtual bool clickedBack() = 0;

	void draw();
	void erase();
	void show();
	void hide();

	inline void setProgramEnd(const bool end) { m_programEnd = end;}
	inline void setGoBack(const bool end) { m_goBack = end;}

	inline const bool getGoBack() const { return m_goBack;}
	inline const bool getProgramEnd() const { return m_programEnd;}
    inline const size_t getDisplayWidth() const { return m_windowWidth; }
    inline const size_t getDisplayHeight() const { return m_windowHeight; }
    inline const std::vector<Menu> getMenus() const { return m_menus; }

protected:
    TDisplayInterface();

    inline std::shared_ptr<SDL_Window> getWindow() const {
        return m_window;
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const
    {
        return m_renderer;
    }

    inline std::shared_ptr<SDL_Event> getSDLEvent() const
    {
        return m_event;
    }

protected:

	//Draw Menus.
	void Initialize();
	virtual void _setDisplay() =0;

	std::vector<Menu> m_menus;

	const tetris::t_size m_windowWidth;
	const tetris::t_size m_windowHeight;

	std::shared_ptr<SDL_Window> m_window;
	std::shared_ptr<SDL_Renderer> m_renderer;
	std::shared_ptr<SDL_Event> m_event;
	std::string m_backgroundImgPath;

	bool m_goBack;
	bool m_programEnd;
};

SDL_TETRIS_END
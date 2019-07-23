#pragma once

#include <string>
#include <vector>

#include "TType.h"

SDL_TETRIS_BEGIN

typedef struct Menu
{
	Point point;
	Font font;
	std::string menustring;
	Color color;
};


class DisplayInterface
{
public:
	inline const size_t getDisplayWidth() { return DISPLAY_WIDTH; }
	inline const size_t getDisplayHeight() { return DISPLAY_HEIGHT; }
	inline const std::vector<Menu> getMenus() { return m_menus; }

	virtual ~DisplayInterface() {}
	virtual bool clickedBack() = 0;

	void Draw();
	void Erase();

protected:
	DisplayInterface(const std::vector<Menu> menus)
	{
		Initialize();
	}

private:
	//Draw Menus.
	void Initialize();
	
	static constexpr size_t DISPLAY_WIDTH = 600;
	static constexpr size_t DISPLAY_HEIGHT = 1200;

	std::vector<Menu> m_menus;
};

SDL_TETRIS_END
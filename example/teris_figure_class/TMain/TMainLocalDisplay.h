#pragma once

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainLocalDisplay : public TMainDisplay, public boost::serialization::singleton<TMainLocalDisplay>
{
public:

	virtual bool clickedEnterServer() override;
	virtual bool clickedStartLocalGame() override;
	virtual bool clickedBack() override;

    static std::shared_ptr<TMainDisplay> getInstance(const std::vector<Menu>& menus);
	static std::shared_ptr<TMainDisplay> getInstance(std::vector<Menu>&& menus);

protected:


private:
    TMainLocalDisplay(const std::vector<Menu>& menus);
    TMainLocalDisplay(std::vector<Menu>&& menus);

	//메뉴 초기화하기.
	virtual void Initialize();
    virtual void _setDisplay() override;
};

SDL_TETRIS_END

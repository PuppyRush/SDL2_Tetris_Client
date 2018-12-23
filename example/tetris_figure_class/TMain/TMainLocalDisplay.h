#pragma once

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainLocalDisplay : public TMainDisplay, public boost::serialization::singleton<TMainLocalDisplay>
{
public:
  //  friend class boost::serialization::singleton<TMainLocalDisplay>;
    enum class UIResource : t_type
	{
		Start,
		Option,
		End
	};


	virtual bool clickedEnterServer() override;
	virtual bool clickedStartLocalGame() override;
	virtual bool clickedBack() override;

    static std::shared_ptr<TMainDisplay> getInstance();



protected:


private:
	TMainLocalDisplay();
	//메뉴 초기화하기.
    virtual void _setDisplay() override;
};

SDL_TETRIS_END

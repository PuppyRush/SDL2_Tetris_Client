#pragma once

#include <vector>
//#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainLocalDisplay final : public TMainDisplay
{
public:
  //  friend class boost::serialization::singleton<TMainLocalDisplay>;
    enum class UIResource : t_type
	{
		Start,
		Option,
		End
	};


	virtual bool clickedEnterServer() final;
	virtual bool clickedStartLocalGame() final;
	virtual bool clickedBack(const TDisplay disply) final;

    static std::shared_ptr<TMainDisplay> getInstance();



protected:


private:
	TMainLocalDisplay();

	virtual void _preInitialize() final;
	virtual void _event(const SDL_Event* event) final;
	virtual void _timer() final;
    virtual void _draw() final;
};

SDL_TETRIS_END

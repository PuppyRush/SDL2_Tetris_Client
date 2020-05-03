#pragma once
#ifndef SDL2_TETRIS_SERVER_TOOL_SCOPETIMER_H
#define SDL2_TETRIS_SERVER_TOOL_SCOPETIMER_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include "../src/Tool/Time/TimerBasic.h"

namespace game_interface::time {

template <typename _Rep, typename _Rn = long long>
class ScopeTimer : protected TimerBasic<_Rep, _Rn>
{
	using Base = TimerBasic<precision>;

	using precision = _Rep;
	using time_point = typename Base::time_point;

public:
	ScopeTimer(TimerSet<_Rep>& set)
		:Base(set)
	{
		set.startPoint = Base::now();
	}

	virtual ~ScopeTimer()
	{
		m_timeset.endPoint = Base::now();

		_cal_duration();
	}

};

}


#endif

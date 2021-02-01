#pragma once
#ifndef EASYTIMER_SCOPETIMER_H
#define EASYTIMER_SCOPETIMER_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include "TimerBasic.h"

namespace easytimer {

template <typename _Rep, typename _Rn = long long>
class ScopeTimer : protected TimerBasic<_Rep, _Rn>
{
	using precision = _Rep;
	using Base = TimerBasic<precision>;
	using time_point = typename Base::time_point;

public:
	ScopeTimer(TimerSet<_Rep>& set)
		:Base(set)
	{
		set.startPoint = Base::now();
	}

	virtual ~ScopeTimer()
	{
		this->m_timeset.endPoint = Base::now();

		this->_cal_duration();
	}

};

}


#endif

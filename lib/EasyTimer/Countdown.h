#pragma once
#ifndef SDL2_TETRIS_SERVER_TOOL_COUNTDOWN_H
#define SDL2_TETRIS_SERVER_TOOL_COUNTDOWN_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <boost/date_time.hpp>

#include "TimerBasic.h"

namespace easytimer {

template <typename _Rep, typename _Rn = long long>
class Countdown : protected TimerBasic<_Rep, _Rn>
{
public:
	using precision = _Rep;
	using range = _Rn;
	using Base = TimerBasic<precision, range>;
	using clock_type = Base::clock_type;
	using duration = Base::duration;
	using time_point = Base::time_point;
	using callback_fn = std::function<void(void*)>;

	enum class TimeType : char
	{
		until_,
		for_
	};

	//for
	Countdown(const callback_fn fn, void* arg, const TimeInfo<>& ti) :m_callback(fn), m_callbackArg(arg), m_timetype(TimeType::until_), m_timeset(ti){}
	Countdown(const callback_fn fn, void* arg, TimeInfo<>&& ti) :m_callback(fn), m_callbackArg(arg), m_timetype(TimeType::until_), m_timeset(ti) {}


	//until today
	Countdown(const callback_fn fn, void* arg, const time_point& tp) :m_callback(fn), m_callbackArg(arg), m_timetype(TimeType::for_), m_timepoint(tp) {}
	Countdown(const callback_fn fn, void* arg, time_point&& tp) :m_callback(fn), m_callbackArg(arg), m_timetype(TimeType::for_), m_timepoint(tp) {}
	~Countdown() = default;

	void start()
	{
		if (m_stop)
		{
			return;
		}

		m_thread = std::thread{ &Countdown::_run_countdown, this };
		{
			std::unique_lock<std::mutex> lk(m_mutex);
			if(m_timetype == TimeType::for_)
			{
				auto dur = m_timepoint - Base::now();
				if (dur < duration{ 0 })
				{
					//err
					dur = duration{ 0 };
				}
				else
				{
					m_duration = dur;
				}
			}
			else
			{
				time_point scheduile_time = Base::now();
				time_point now = scheduile_time;
				
				if constexpr (std::is_same<precision, std::milli>::value)
				{
					scheduile_time += m_timeset.hours;
					scheduile_time += m_timeset.minutes;
					scheduile_time += m_timeset.seconds;
					scheduile_time += m_timeset.milliseconds;
				}

				if constexpr (std::is_same<precision, std::micro>::value)
				{
					scheduile_time += m_timeset.hours;
					scheduile_time += m_timeset.minutes;
					scheduile_time += m_timeset.seconds;
					scheduile_time += m_timeset.milliseconds;
					scheduile_time += m_timeset.microseconds;
				}

				if constexpr (std::is_same<precision, std::nano>::value)
				{
					scheduile_time += m_timeset.hours;
					scheduile_time += m_timeset.minutes;
					scheduile_time += m_timeset.seconds;
					scheduile_time += m_timeset.milliseconds;
					scheduile_time += m_timeset.microseconds;
					scheduile_time += m_timeset.nanoseconds;
				}

				m_duration = scheduile_time - now;
			}

			//std::cout << "m_dur : " << easytimer::get_duration_string(m_duration) << std::endl;
		}
	}

	void suspend()
	{
		if (m_stop)
		{
			assert(0);
			return;
		}

		m_suspended = true;
		m_cv.notify_one();
	}

	void resume()
	{
		if (m_stop)
		{
			assert(0);
			return;
		}

		m_suspended = false;
		m_cvSuspend.notify_one();
	}

	void stop()
	{
		m_stop = true;
		m_suspended = false;
		m_cv.notify_one();
		m_cvSuspend.notify_one();
	}

	void join()
	{
		m_thread.join();
	}


protected:

	Countdown(const callback_fn fn, void* arg) :m_callback(fn), m_callbackArg(arg), m_timetype(TimeType::for_)
	{}


private:

	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::condition_variable m_cvSuspend;
	std::thread m_thread;

	TimeType m_timetype;
	TimeInfo<> m_timeset;
	time_point m_timepoint;
	bool m_suspended = false;
	duration m_duration;
	bool m_stop = false;

	callback_fn m_callback;
	void* m_callbackArg = nullptr;

	void _run_countdown()
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		bool result = true;

		std::cout << "countdown start" << easytimer::get_time_string(Base::now()) << std::endl;

		while (result)
		{
			result = m_cv.wait_until(lk, clock_type::now() + m_duration, [=]() {return m_suspended || m_stop; });
			
			//std::cout << "countdown suspended" << easytimer::get_time_string<easytimer::nanoseconds>(Base::now()) << std::endl;

			m_cvSuspend.wait(lk, [=]() {return !m_suspended || !m_stop; });

			//std::cout << "countdown suspended2" << easytimer::get_time_string<easytimer::nanoseconds>(Base::now()) << std::endl;

		}

		std::cout << "countdown end  " << easytimer::get_time_string(Base::now()) << std::endl;
		 
		m_callback(m_callbackArg);
	}
};

}


#endif

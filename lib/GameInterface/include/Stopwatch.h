#pragma once
#ifndef SDL2_TETRIS_SERVER_TOOL_STOPWATCH_H
#define SDL2_TETRIS_SERVER_TOOL_STOPWATCH_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include <queue>
#include <deque>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <stdexcept>

#include "../src/Tool/Time/TimerBasic.h"


namespace game_interface::time {

template <typename _Rep, typename _Rn = long long>
class Stopwatch : protected TimerBasic<_Rep, _Rn>{

public:
	using precision = _Rep;
	using range = _Rn;
	using Base = TimerBasic<precision, range>;
	using clock_type = Base::clock_type;
	using duration = Base::duration;
	using time_point = Base::time_point;
	using ary_type = std::deque<TimeInfo<_Rn>>;

	Stopwatch() = default;

	~Stopwatch()
	{
		end();
	}


	void start() noexcept
	{
		Base::start();
		m_lastTimepoint = Base::start_point();

		m_doRunning = true;
		m_stopwatchThread = std::thread(&Stopwatch::_RepocStopwatchCalculation, this);
	}

	void end()
	{
		Base::end();

		if (m_doRunning)
		{
			m_doRunning = false;
			m_threadStopSignal.notify_one();
			m_stopwatchThread.join();
		}
	}

	void do_record()
	{
		m_cal_q.emplace(Recordset{ Base::now(), m_suspendedDuration });
		m_threadStopSignal.notify_one();
		this->m_suspendedDuration = { 0 };
	}
	
	inline const ary_type& get_record() const noexcept
	{
		return m_record;
	}

	void remove_last()
	{
		if (m_record.empty())
		{
			throw std::range_error{};
		}
		m_record.pop_back();
	}

	void remove_first()
	{
		if (m_record.empty())
		{
			throw std::range_error{};
		}
		m_record.pop_front();
	}

	TimeInfo<_Rn> operator[] (const int i) const
	{
		if (m_record.size() <= i)
		{
			throw std::range_error{};
		}
		return m_record.at(i);
	}

	auto count() const noexcept
	{
		return m_record.size();
	}

	void suspend()
	{
		Base::suspend();
	}

	void resume()
	{
		Base::resume();
	}

private:

	struct Recordset
	{
		time_point timePoint;
		duration dur;
	};

	ary_type m_record;
	time_point m_lastTimepoint;

	std::queue<Recordset> m_cal_q;

	std::atomic<bool> m_doRunning = false;
	std::mutex m_threadStopMutex;
	std::condition_variable m_threadStopSignal;
	std::thread m_stopwatchThread;

	void _RepocStopwatchCalculation()
	{
		std::unique_lock<std::mutex> lock(m_threadStopMutex);
		
		while (m_doRunning)
		{
			m_threadStopSignal.wait(lock, [=]() { return !m_cal_q.empty() || !m_doRunning; });
			if (!m_doRunning)
				break;

			Recordset time = m_cal_q.front();
			m_cal_q.pop();

			TimeInfo timeset;

			if constexpr (std::is_same< std::nano, precision>::value)
			{
				auto nano_last = time::time_point_cast<nanoseconds>(m_lastTimepoint);
				auto nano_now = time::time_point_cast<nanoseconds>(time.timePoint);
				timeset.nanoseconds = (nano_now - nano_last);
		
				timeset.nanoseconds -= (time.dur*2);

				if (timeset.nanoseconds > nanoseconds{ 0 })
				{
					timeset.microseconds = time_rest<microseconds>(timeset.nanoseconds);
				}
				if (timeset.microseconds > microseconds{ 0 })
				{
					timeset.milliseconds = time_rest<milliseconds>(timeset.nanoseconds);
				}
				if (timeset.milliseconds > milliseconds{ 0 })
				{
					timeset.seconds = time_rest<seconds>(timeset.nanoseconds);
				}
				if (timeset.seconds > seconds{ 0 })
				{
					timeset.minutes = time_rest<minutes>(timeset.nanoseconds);
				}
				if (timeset.minutes > minutes{ 0 })
				{
					timeset.hours = time_rest<hours>(timeset.nanoseconds);
				}
			}
			std::cout << timeset.nanoseconds.count() << std::endl;
			timeset.nanoseconds %= time::nanoseconds{ 1000 };
			m_record.push_back(timeset);

			m_lastTimepoint = time.timePoint;
		}
	}
};

}


#endif

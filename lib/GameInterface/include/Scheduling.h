#pragma once
#ifndef SDL2_TETRIS_SERVER_TOOL_SCHEDULING_H
#define SDL2_TETRIS_SERVER_TOOL_SCHEDULING_H


#if _MSC_VER >= 1200
#pragma once
#endif

#include <ctime>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <deque>
#include <set>



#include "Countdown.h"
#include "Date.h"
#include "Times.h"

namespace game_interface::time {


struct SchedulingBuilderBase;


class Scheduling : protected TimerBasic< std::ratio<1> , long long > {

public:
	using rep = std::ratio<1>;
	using period = long long;
	using duration = std::chrono::duration< period, rep>;
	using Base = TimerBasic< rep, period>;
	using time_point = typename Base::time_point;
	using triggerQueue = std::deque<time_point>;
	using callback_fn = std::function<void(void*)>;

	enum class repeat : char
	{
		just_one,
		daily,
		weekly,
		monthly
	};

	struct TimeSet
	{
	public:
		date::DateInfo dateset;
		time::hours hours{ 0 };
		time::minutes minutes{ 0 };
		time::seconds seconds{ 0 };

		TimeSet(date::DateInfo da, int h, int m, int s)
			:dateset(da),hours(h), minutes(m), seconds(s)
		{}

		inline void date(const date::DateInfo d) noexcept
		{
			dateset = d;
		}

		inline void hour(const int h) noexcept
		{
			hours = time::hours{ h };
		}

		inline void minute(const int m) noexcept
		{
			minutes = time::minutes{ m };
		}

		inline void second(const int s) noexcept
		{
			seconds = time::seconds{ s };
		}
	};

	struct SchedulingBuilderBase
	{
	protected:
		using time_point = typename Scheduling::time_point;

		SchedulingBuilderBase() = delete;

		SchedulingBuilderBase(const date::DateInfo& date, Scheduling::repeat rep)
			:m_timeset({ date,0,0,0 }), m_repeated(rep)
		{}

		SchedulingBuilderBase(date::DateInfo&& date, Scheduling::repeat rep)
			:m_timeset({ date,0,0,0 }), m_repeated(rep)
		{}

		time_point _calcTimePoint(const TimeSet timeset)
		{
			using namespace boost::posix_time;
			ptime epoch(boost::gregorian::date(1970, 1, 1));
			time_duration::sec_type x = (ptime{ timeset.dateset } -epoch).total_seconds();
			auto tp = std::chrono::system_clock::from_time_t(time_t(x));
			time_point cv_tp = std::chrono::time_point_cast<Base::duration>(tp);
			cv_tp -= std::chrono::hours{ 9 };

			cv_tp += timeset.hours;
			cv_tp += timeset.minutes;
			cv_tp += timeset.seconds;

			return cv_tp;
		}


	public:
		typename Scheduling::triggerQueue m_triggerTimePoint;

		inline void hour(const int h) noexcept
		{
			m_timeset.hours = time::hours{ h };
		}

		inline void minute(const int m) noexcept
		{
			m_timeset.minutes = time::minutes{ m };
		}

		inline void second(const int s) noexcept
		{
			m_timeset.seconds = time::seconds{ s };
		}


		virtual Scheduling::triggerQueue getTimePoints() = 0;

	
	protected:
		TimeSet m_timeset;
		Scheduling::repeat m_repeated;
	};



	Scheduling() = delete;

	Scheduling(const callback_fn fn, void* arg, SchedulingBuilderBase& schedulingBuilder)
		: m_callback(fn), m_fnArg(arg)
	{
		m_triggerTimePoint = schedulingBuilder.getTimePoints();
	}

	void start()
	{
		for (const auto& tm : m_triggerTimePoint)
		{
			Countdown<rep> cd{ m_callback, m_fnArg, tm };
			cd.start();
			cd.join();
		}
	}

private:

	std::string m_description;
	triggerQueue m_triggerTimePoint;
	callback_fn m_callback;
	void* m_fnArg;
};



struct SchedulingBuilder : public Scheduling::SchedulingBuilderBase
{
public:
	using Base = SchedulingBuilderBase;

	SchedulingBuilder() = delete;

	SchedulingBuilder(const date::DateInfo& date)
		:Base(date, Scheduling::repeat::just_one)
	{}
	
	SchedulingBuilder(date::DateInfo&& date)
		:Base(date, Scheduling::repeat::just_one)
	{}

protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		Scheduling::triggerQueue q;
		q.push_back(_calcTimePoint(Base::m_timeset));

		return q;
	}


};
 
시작시간이 현재시간보다 늦었지만 매일설정 되었을경우 처리
struct SchedulingBuilderDaily : public SchedulingBuilder
{
public:
	using Base = SchedulingBuilder;

	SchedulingBuilderDaily() = delete;

	explicit SchedulingBuilderDaily(date::DateInfo& date, const unsigned char interval, const unsigned char count = 1)
		:Base(date), m_interval(interval), m_count(count)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	explicit SchedulingBuilderDaily(date::DateInfo&& date, const unsigned char interval, const unsigned char count = 1)
		:Base(date), m_interval(interval), m_count(count)
	{
		m_repeated = Scheduling::repeat::daily;
	}


protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		Scheduling::triggerQueue q;

		auto tp = _calcTimePoint(Base::m_timeset);
		q.push_back(tp);

		for (unsigned char i = 1; i <= m_count; i++)
		{
			tp += time::hours{ 24 } * (i*m_interval);
			q.push_back(tp);
		}

		return q;
	}

	unsigned m_interval{ 1 };
	unsigned m_count{ 1 };
	
};


struct SchedulingBuilderWeekly : public SchedulingBuilderDaily
{
public:
	using Base = SchedulingBuilderDaily;

	SchedulingBuilderWeekly() = delete;

	explicit SchedulingBuilderWeekly(date::DateInfo& date, const unsigned char interval, const unsigned char count = 1)
		:Base(date, interval, count)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	explicit SchedulingBuilderWeekly(date::DateInfo&& date, const unsigned char interval, const unsigned char count = 1)
		:Base(date, interval, count)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	void addEveryWeekdays()
	{
		for (int i = boost::date_time::weekdays::Sunday; i <= boost::date_time::weekdays::Saturday; i++)
		{
			weeks.insert(static_cast<boost::date_time::weekdays>(i));
		}
	}

	void addWeekdays(const boost::date_time::weekdays _weekday)
	{
		weeks.insert(_weekday);
	}

	void removeWeekdays(const boost::date_time::weekdays _weekday)
	{
		weeks.erase(_weekday);
	}

	void reverse()
	{

	}


protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		Scheduling::triggerQueue q;

		auto tp = _calcTimePoint(Base::m_timeset);
		q.push_back(tp);

		for (unsigned char i = 1; i <= m_count; i++)
		{
			tp += time::hours{ 24 } *(i * m_interval);
			q.push_back(tp);
		}

		return q;
	}

private:
	std::set< boost::date_time::weekdays > weeks;
};


struct SchedulingBuilderMonthly : public SchedulingBuilder
{
public:
	using Base = SchedulingBuilder;

	SchedulingBuilderMonthly() = delete;

	explicit SchedulingBuilderMonthly(date::DateInfo& date)
		:Base(date)
	{
		Base::m_repeated = Scheduling::repeat::monthly;
	}

	explicit SchedulingBuilderMonthly(date::DateInfo&& date)
		:Base(date)
	{
		Base::m_repeated = Scheduling::repeat::monthly;
	}

	void addEveryMonths()
	{
		for (int i = boost::date_time::months_of_year::Jan; i <= boost::date_time::months_of_year::Dec; i++)
		{
			months.insert(static_cast<boost::date_time::months_of_year>(i));
		}
	}

	void addMonths(const boost::date_time::months_of_year _month)
	{
		months.insert(_month);
	}

	void removeMonths(const boost::date_time::months_of_year _month)
	{
		months.erase(_month);
	}

private:
	std::set< boost::date_time::months_of_year > months;
};


}


#endif

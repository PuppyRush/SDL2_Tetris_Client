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


class Scheduling : protected TimerBasic<std::ratio<1>, long long> {

public:
	using Base = TimerBasic<std::ratio<1>, long long>;
	using time_point = typename Base::time_point;
	using triggerQueue = std::deque<time_point>;
	using callback_fn = std::function<void(void*)>;

	struct SchedulingBuilderBase
	{
	public:
		typename Scheduling::triggerQueue m_triggerTimePoint;

		SchedulingBuilderBase() = default;

		virtual Scheduling::triggerQueue getTimePoints() = 0;

	};


	enum class repeat : char
	{
		just_one,
		daily,
		weekly,
		monthly
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
			Countdown<std::ratio<1>> cd{ m_callback, m_fnArg, tm };
			cd.start();
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
	using Base = Scheduling;

	SchedulingBuilder() = delete;

	SchedulingBuilder(const date::DateInfo& date)
		:startDate(date), m_repeated(Base::repeat::just_one)
	{}
	
	SchedulingBuilder(date::DateInfo&& date)
		:startDate(date), m_repeated(Base::repeat::just_one)
	{}

	inline void hour(const date::hours h) noexcept
	{
		hours = date::hours{ h };
	}

	inline void minute(const date::minutes m) noexcept
	{
		minutes = date::minutes{ m };
	}

	inline void second(const date::seconds s) noexcept
	{
		seconds = date::seconds{ s };
	}

protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		using namespace boost::posix_time;
		ptime epoch{ startDate };
		time_duration::sec_type x = (epoch - from_time_t(time::now_to_time())).total_seconds();
		auto tt = time_t(x);

		auto tp =  std::chrono::system_clock::from_time_t(tt);

		return Scheduling::triggerQueue{};
	}


protected:
	date::DateInfo startDate;

	date::hours hours{ 0 };
	date::minutes minutes{ 0 };
	date::seconds seconds{ 0 };

	Base::repeat m_repeated;
};

struct SchedulingBuilderDaily : public SchedulingBuilder
{
public:
	using Base = SchedulingBuilder;

	SchedulingBuilderDaily() = delete;

	explicit SchedulingBuilderDaily(date::DateInfo& date, const short interval)
		:Base(date), m_interval(interval)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	explicit SchedulingBuilderDaily(date::DateInfo&& date, const short interval)
		:Base(date), m_interval(interval)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	short m_interval;
	
};


struct SchedulingBuilderWeekly : public SchedulingBuilderDaily
{
public:
	using Base = SchedulingBuilderDaily;

	SchedulingBuilderWeekly() = delete;

	explicit SchedulingBuilderWeekly(date::DateInfo& date, const short interval )
		:Base(date, interval)
	{
		Base::m_repeated = Scheduling::repeat::daily;
	}

	explicit SchedulingBuilderWeekly(date::DateInfo&& date, const short interval )
		:Base(date, interval)
	{
		Base::m_repeated = Scheduling::repeat::daily;
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

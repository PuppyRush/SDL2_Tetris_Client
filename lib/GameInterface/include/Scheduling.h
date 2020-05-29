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
#include <type_traits>


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
	using clock_type = Base::clock_type;
	using time_point = typename Base::time_point;
	using triggerQueue = std::deque<time_point>;
	using callback_fn = std::function<void(void*)>;

	enum class repeat : char
	{
		just_one,
		daily,
		weekly,
		monthly,
		manually
	};

	struct DateTime
	{
	public:

		date::DateInfo dateset;
		time::hours hours{ 0 };
		time::minutes minutes{ 0 };
		time::seconds seconds{ 0 };

		DateTime(date::DateInfo da, int h, int m, int s)
			:dateset(da),hours(h), minutes(m), seconds(s)
		{}

		bool operator< (const DateTime& rhs) const
		{
			if (this->dateset < rhs.dateset)
				return true;
			else if (this->dateset > rhs.dateset)
				return false;
			else
			{
				if (this->hours < rhs.hours)
					return true;
				else if (this->hours > rhs.hours)
					return false;
				else
				{
					if (this->minutes < rhs.minutes)
						return true;
					else if (this->minutes > rhs.minutes)
						return false;
					else
					{
						if (this->minutes < rhs.minutes)
							return true;
						else if (this->minutes > rhs.minutes)
							return false;
					}
				}
			}
		}

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

		void operator+=(const time_point pt)
		{

		}
	};

	struct SchedulingBuilderBase
	{
	protected:
		using time_point = typename Scheduling::time_point;

		SchedulingBuilderBase() = delete;

		SchedulingBuilderBase(const Scheduling::DateTime date , Scheduling::repeat rep)
			:m_startDatetime(date), m_repeated(rep)
		{}

		SchedulingBuilderBase(const date::DateInfo& date, Scheduling::repeat rep)
			:m_startDatetime({ date,0,0,0 }), m_repeated(rep)
		{}

		SchedulingBuilderBase(date::DateInfo&& date, Scheduling::repeat rep)
			:m_startDatetime({ date,0,0,0 }), m_repeated(rep)
		{}


	public:
		typename Scheduling::triggerQueue m_triggerTimePoint;

		inline void hour(const int h) noexcept
		{
			m_startDatetime.hours = time::hours{ h };
		}

		inline void minute(const int m) noexcept
		{
			m_startDatetime.minutes = time::minutes{ m };
		}

		inline void second(const int s) noexcept
		{
			m_startDatetime.seconds = time::seconds{ s };
		}

		inline void expire(const DateTime expire) noexcept
		{
			m_expireTime = expire;
		}

		DateTime getExpire() const noexcept
		{
			return m_expireTime;
		}

		DateTime getStartDateTime() const noexcept
		{
			return m_startDatetime;
		}

		virtual Scheduling::triggerQueue getTimePoints() = 0;

	
	protected:
		DateTime m_startDatetime;
		DateTime m_expireTime{ date::DateInfo{},0,0,0, };
		Scheduling::repeat m_repeated;
	};



	Scheduling() = delete;

	Scheduling(const callback_fn fn, void* arg, SchedulingBuilderBase& schedulingBuilder)
		: m_callback(fn), m_fnArg(arg), m_expireTime(Scheduling::_DateTime_to_timepoint( schedulingBuilder.getExpire() ))
	{
		m_triggerTimePoint = schedulingBuilder.getTimePoints();
	}

	void start()
	{
		for (const auto& tm : m_triggerTimePoint)
		{
			if (tm < Base::now())
			{
				continue;
			}
			else if (tm > m_expireTime)
			{
				continue;
			}
			Countdown<rep> cd{ m_callback, m_fnArg, tm };
			cd.start();
			cd.join();
		}
	}

	//date시점을 time_point로 변환
	static time_point _DateTime_to_timepoint(const DateTime DateTime)
	{
		using namespace boost::posix_time;
		ptime epoch(boost::gregorian::date(1970, 1, 1));
		time_duration::sec_type x = (ptime{ DateTime.dateset } -epoch).total_seconds();
		auto tp = std::chrono::system_clock::from_time_t(time_t(x));
		time_point cv_tp = std::chrono::time_point_cast<Base::duration>(tp);
		cv_tp -= std::chrono::hours{ 9 };

		cv_tp += DateTime.hours;
		cv_tp += DateTime.minutes;
		cv_tp += DateTime.seconds;

		return cv_tp;
	}

private:

	std::string m_description;
	triggerQueue m_triggerTimePoint;
	time_point m_expireTime{ std::numeric_limits<time_point>::max() };
	callback_fn m_callback;
	void* m_fnArg;
};



struct SchedulingBuilder : public Scheduling::SchedulingBuilderBase
{
public:
	using Base = SchedulingBuilderBase;

	SchedulingBuilder() = delete;

	SchedulingBuilder(const Scheduling::DateTime date)
		:Base(date, Scheduling::repeat::just_one)
	{}

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
		q.push_back( Scheduling::_DateTime_to_timepoint(Base::m_startDatetime));

		return q;
	}


};
 
struct SchedulingBuilderManually : public SchedulingBuilder
{
public:
	using Base = SchedulingBuilder;

	SchedulingBuilderManually() = delete;

	SchedulingBuilderManually(Scheduling::DateTime& date)
		:Base(date)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	SchedulingBuilderManually(Scheduling::DateTime&& date)
		:Base(date)
	{
		m_repeated = Scheduling::repeat::daily;
	}
	
	void addTimepoint(const Scheduling::DateTime datetime)
	{
		m_dateTimeSet.insert(datetime);
	}


protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		Scheduling::triggerQueue q;
		
		for(const auto& time : m_dateTimeSet)
		{ 
			q.push_back(Scheduling::_DateTime_to_timepoint(time));
		}

		return q;
	}

	unsigned m_interval{ 1 };
	unsigned m_count{ 1 };
	std::set<Scheduling::DateTime> m_dateTimeSet;
};


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

		auto tp = Scheduling::_DateTime_to_timepoint(Base::m_startDatetime);
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

	using weekdays = boost::date_time::weekdays;

	SchedulingBuilderWeekly() = delete;

	explicit SchedulingBuilderWeekly(date::DateInfo& date, const unsigned char count = 1)
		:Base(date, 0, count)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	explicit SchedulingBuilderWeekly(date::DateInfo&& date, const unsigned char count = 1)
		:Base(date, 0, count)
	{
		m_repeated = Scheduling::repeat::daily;
	}

	void addEveryWeekdays()
	{
		for (int i = weekdays::Sunday; i <= weekdays::Saturday; i++)
		{
			weeks.insert(static_cast<weekdays>(i));
		}
	}

	void addWeekdays(const weekdays _weekday)
	{
		weeks.insert(_weekday);
	}

	void removeWeekdays(const weekdays _weekday)
	{
		weeks.erase(_weekday);
	}

	void reverse()
	{

	}


protected:

	virtual Scheduling::triggerQueue getTimePoints() override
	{
		//week what?
		auto startWeekday = Base::getStartDateTime().dateset.day_of_week();
		auto start_timepoint = Scheduling::_DateTime_to_timepoint(Base::m_startDatetime);
		std::deque<weekdays> nextweek;
		std::deque<weekdays> thisweek;
		
		//resolve startDate
		auto today = date::get_today();
		if (auto startDate_as_enum = boost::gregorian::greg_weekday{ startWeekday }.as_enum();
			today < startDate_as_enum)
		{
			thisweek.push_back(startDate_as_enum);
		}
		else if (today == startDate_as_enum)
		{
			if (Scheduling::clock_type::to_time_t(start_timepoint) >= time::now_to_time())
			{
				thisweek.push_back(startDate_as_enum);
			}
		}

		//resolve added date
		for (const auto week : weeks)
		{
			if (week < startWeekday)
			{
				nextweek.push_back(week);
			}
			else if(week > startWeekday)
			{
				thisweek.push_back(week);
			}
			else
			{
			
				if (Scheduling::clock_type::to_time_t(start_timepoint) < time::now_to_time())
				{
					nextweek.push_back(week);
				}
				else
				{
					thisweek.push_back(week);
				}
			}
		}

		//sum weekdays
		Scheduling::triggerQueue q;
		for (int i = 1; i <= m_count; i++)
		{
			for (auto w : thisweek)
			{
				int ch = w - startWeekday;

				auto t = start_timepoint + time::hours{ 24 }*ch; 
				t += time::hours{ 24 }*((i - 1) * 7);
				q.push_back(t);

				std::cout << "week time : " << time::get_time_string(t) << std::endl;
			}

			for (auto w : nextweek)
			{
				int ch = w - startWeekday + 7;

				auto t = start_timepoint + time::hours{ 24 }*ch;
				t += time::hours{ 24 }*((i - 1) * 7);
				q.push_back(t);

				std::cout << "week time : " << time::get_time_string(t) << std::endl;
			}
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


#include <ctime>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace date
{
    using years =  std::int16_t;//boost::gregorian::gregorian_calendar::year_type;
    using months = std::int16_t;//boost::gregorian::gregorian_calendar::month_type;
    using days =   std::int16_t;//boost::gregorian::gregorian_calendar::day_type;

    using hours = std::int8_t;
    using minutes = std::int8_t;
    using seconds = std::int8_t;

    using DateInfo = boost::gregorian::date;

  /*  struct DateInfo
    {
        years years;
        months months;
        days days;

        DateInfo(date::years _y, date::months _m, date::days _d)
            :years(_y), months(_m), days(_d)
        {
        }

        inline void year(const date::years y) noexcept
        {
            years = date::years{ y };
        }

        inline void month(const date::months m) noexcept
        {
            months = date::months{ m };
        }

        inline void day(const date::days d) noexcept
        {
            days = date::days{ d };
        }
    };*/

    template <class _Tp>
    static boost::gregorian::date get_date_from(const _Tp& tp)
    {
        return boost::gregorian::date_from_tm(clock_type::to_time_t(date::time_point<clock_type::duration>(tp)));
    }

    static boost::gregorian::date get_date_from(const std::time_t t)
    {
        std::tm* now = std::localtime(&t);
        return boost::gregorian::date_from_tm(*now);
    }

    static boost::gregorian::date get_date_from(const std::tm& _tm)
    {
        return boost::gregorian::date_from_tm(_tm);
    }

    static boost::gregorian::date get_now_date()
    {
        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);
        return boost::gregorian::date_from_tm(*now);
    }

    static std::time_t to_time_t(const boost::gregorian::date& date) {
        using namespace boost::posix_time;
        static ptime epoch(boost::gregorian::date(1970, 1, 1));
        time_duration::sec_type secs =  ( ptime{date }  - epoch).total_seconds();
        return time_t(secs);
    }
}

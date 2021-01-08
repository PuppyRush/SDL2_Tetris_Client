
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

    static boost::date_time::weekdays get_today()
    {
        using namespace boost::gregorian;
        boost::gregorian::date today{ day_clock::local_day() };
        greg_weekday wd = today.day_of_week(); 
        return wd.as_enum();
    }

    template <class _Tp>
    static boost::gregorian::date get_date_from(const _Tp& tp)
    {
        return boost::gregorian::date_from_tm(easytimer::clock_type::to_time_t( time_point< easytimer::clock_type::duration>(tp)));
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

//
// Created by chaed on 19. 5. 5.
//

#ifndef GAMEINTERFACE_TIME_H
#define GAMEINTERFACE_TIME_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <ctime>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>

#include <boost/date_time/gregorian/gregorian.hpp>
#include "boost/date_time/posix_time/conversion.hpp"

#include "Configcpp.h"

namespace game_interface::time {

    using hours = std::chrono::hours;
    using seconds = std::chrono::seconds;
    using minutes = std::chrono::minutes;
    using milliseconds = std::chrono::milliseconds;
    using microseconds = std::chrono::microseconds;
    using nanoseconds = std::chrono::nanoseconds;

    using clock_type = std::chrono::system_clock;

    template <typename _Rn = long long>
    struct TimeInfo
    {
    public:
        using range = _Rn;

        time::hours hours{ 0 };
        time::minutes minutes{ 0 };
        time::seconds seconds{ 0 };
        time::milliseconds milliseconds{ 0 };
        time::microseconds microseconds{ 0 };
        time::nanoseconds nanoseconds{ 0 };

        TimeInfo(range h = 0, range m = 0, range s = 0, range milli = 0, range mic = 0, range nano = 0)
            :hours(time::hours{ h }), minutes(time::minutes{ m }), seconds(time::seconds{ s }),
            milliseconds(time::milliseconds{ milli }), microseconds(time::microseconds{ mic }), nanoseconds(time::nanoseconds{ nano })
        {}

        inline void hour(const range& h) noexcept
        {
            hours = hours{ h };
        }

        inline void minuet(const range& m) noexcept
        {
            minuets = minuets{ m };
        }

        inline void second(const range& s) noexcept 
        {
            seconds = seconds{ s };
        }

        inline void millisecond(const range& m) noexcept
        {
            milliseconds = milliseconds{ m };
        }

        inline void microsecond(const range& m) noexcept
        {
            microseconds = microseconds{ m };
        }

        inline void nanosecond(const range& n) noexcept
        {
            nanoseconds = nanoseconds{ n };
        }

        template <typename _Rn = long long>
        static TimeInfo<_Rn> now()
        {
           // TimeInfo<_Rn> ti;
            
        }

    };

    static __inline std::time_t now_to_time()
    {
        return ::time(nullptr);
    }

    template<typename _From>
    inline static time::hours _time_rest(_From time, time::hours)
    {
        return std::chrono::duration_cast<time::hours>(time) % time::hours{ 12 };
    }

    template<typename _From>
    inline static time::minutes _time_rest(_From time, time::minutes)
    {
        return std::chrono::duration_cast<time::minutes>(time) % time::minutes{ 60 };
    }

    template<typename _From>
    inline static time::seconds _time_rest(_From time, time::seconds)
    {
        return std::chrono::duration_cast<time::seconds>(time) % time::seconds{ 60 };
    }

    template<typename _From>
    inline static time::milliseconds _time_rest(_From time, time::milliseconds)
    {
        return std::chrono::duration_cast<time::milliseconds>(time) % time::milliseconds{ 1000 };
    }

    template<typename _From>
    inline static time::microseconds _time_rest(_From time, time::microseconds)
    {
        return std::chrono::duration_cast<time::microseconds>(time) % time::microseconds{ 1000 };
    }

    template<typename _From>
    inline static time::nanoseconds _time_rest(_From time, time::nanoseconds)
    {
        return std::chrono::duration_cast<time::nanoseconds>(time) % time::nanoseconds{ 1000 };
    }

    template<typename _To, typename _From>
    inline static _To time_rest(_From t)
    {
        return _time_rest(t, _To{});
    }

    template <class _Dur>
    static std::string get_duration_string(const _Dur dur)
    {
        auto nano = time::time_rest<time::nanoseconds>(dur);
        auto micro = time::time_rest<time::microseconds>(dur);
        auto mili = time::time_rest<time::milliseconds>(dur);
        auto sec = time::time_rest<seconds>(dur);
        auto min = time::time_rest<minutes>(dur);
        auto h = time::time_rest<hours>(dur);

        std::stringstream sstream;
        sstream << h.count() << " " << min.count() << " " << sec.count() << " " << mili.count() << " " << micro.count() << " " << nano.count();
        return sstream.str();
    }

    template <class T>
    static std::string get_time_string(const T t)
    {
        std::time_t tt = T::clock::to_time_t(time::time_point_cast<time::clock_type::duration>(t));

        std::stringstream sstream;
        sstream << std::put_time(std::localtime(&tt), "%c");

        sstream << " " << time::time_rest<time::milliseconds>(t.time_since_epoch()).count();
        sstream << " " << time::time_rest<time::microseconds>(t.time_since_epoch()).count();
        sstream << " " << time::time_rest<time::nanoseconds>(t.time_since_epoch()).count();

        return sstream.str();
    }

    static std::string get_time_string(const std::time_t t)
    {
        return get_time_string(
                time::clock_type::from_time_t(t));
    }


    template <typename _Dur, typename _From>
    constexpr std::chrono::time_point<typename _From::clock, _Dur> time_point_cast(const _From src_time_point) noexcept
    {
        using duration = std::chrono::duration<typename _Dur::rep, typename _Dur::period>;
        return std::chrono::time_point_cast<duration, typename _From::clock, typename _From::duration>(src_time_point);
    }

  
}


#endif //GAMEINTERFACE_TIME_H

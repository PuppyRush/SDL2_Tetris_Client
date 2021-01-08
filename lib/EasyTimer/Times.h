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

namespace easytimer {

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

        easytimer::hours hours{ 0 };
        easytimer::minutes minutes{ 0 };
        easytimer::seconds seconds{ 0 };
        easytimer::milliseconds milliseconds{ 0 };
        easytimer::microseconds microseconds{ 0 };
        easytimer::nanoseconds nanoseconds{ 0 };

        TimeInfo(range h = 0, range m = 0, range s = 0, range milli = 0, range mic = 0, range nano = 0)
            :hours(easytimer::hours{ h }), minutes(easytimer::minutes{ m }), seconds(easytimer::seconds{ s }),
            milliseconds(easytimer::milliseconds{ milli }), microseconds(easytimer::microseconds{ mic }), nanoseconds(easytimer::nanoseconds{ nano })
        {}

        inline void hour(const range& h) noexcept
        {
            hours = easytimer::hours{ h };
        }

        inline void minuet(const range& m) noexcept
        {
            minutes = easytimer::minutes{ m };
        }

        inline void second(const range& s) noexcept 
        {
            seconds = easytimer::seconds{ s };
        }

        inline void millisecond(const range& m) noexcept
        {
            milliseconds = easytimer::milliseconds{ m };
        }

        inline void microsecond(const range& m) noexcept
        {
            microseconds = easytimer::microseconds{ m };
        }

        inline void nanosecond(const range& n) noexcept
        {
            nanoseconds = easytimer::nanoseconds{ n };
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
    inline static easytimer::hours _time_rest(_From time, easytimer::hours)
    {
        return std::chrono::duration_cast<easytimer::hours>(time) % easytimer::hours{ 12 };
    }

    template<typename _From>
    inline static easytimer::minutes _time_rest(_From time, easytimer::minutes)
    {
        return std::chrono::duration_cast<easytimer::minutes>(time) % easytimer::minutes{ 60 };
    }

    template<typename _From>
    inline static easytimer::seconds _time_rest(_From time, easytimer::seconds)
    {
        return std::chrono::duration_cast<easytimer::seconds>(time) % easytimer::seconds{ 60 };
    }

    template<typename _From>
    inline static easytimer::milliseconds _time_rest(_From time, easytimer::milliseconds)
    {
        return std::chrono::duration_cast<easytimer::milliseconds>(time) % easytimer::milliseconds{ 1000 };
    }

    template<typename _From>
    inline static easytimer::microseconds _time_rest(_From time, easytimer::microseconds)
    {
        return std::chrono::duration_cast<easytimer::microseconds>(time) % easytimer::microseconds{ 1000 };
    }

    template<typename _From>
    inline static easytimer::nanoseconds _time_rest(_From time, easytimer::nanoseconds)
    {
        return std::chrono::duration_cast<easytimer::nanoseconds>(time) % easytimer::nanoseconds{ 1000 };
    }

    template<typename _To, typename _From>
    inline static _To time_rest(_From t)
    {
        return _time_rest(t, _To{});
    }

    template <class _Dur>
    static std::string get_duration_string(const _Dur dur)
    {
        auto nano = easytimer::time_rest<easytimer::nanoseconds>(dur);
        auto micro = easytimer::time_rest<easytimer::microseconds>(dur);
        auto mili = easytimer::time_rest<easytimer::milliseconds>(dur);
        auto sec = easytimer::time_rest<seconds>(dur);
        auto min = easytimer::time_rest<minutes>(dur);
        auto h = easytimer::time_rest<hours>(dur);

        std::stringstream sstream;
        sstream << std::setfill('0') << std::setw(2);

        sstream << h.count() << " " << min.count() << " " << sec.count() << " " << mili.count() << " " << micro.count() << " " << nano.count();
        return sstream.str();
    }

    template <class T>
    static std::string get_time_string(const T t)
    {
        std::time_t tt = T::clock::to_time_t( time_point_cast<easytimer::clock_type::duration>(t));

        std::stringstream sstream;
        sstream << std::setfill('0') << std::setw(2);
        sstream.width(2);

        sstream << std::put_time(std::localtime(&tt), "%c");

        sstream << " " << easytimer::time_rest<easytimer::milliseconds>(t.time_since_epoch()).count();
        sstream << " " << easytimer::time_rest<easytimer::microseconds>(t.time_since_epoch()).count();
        sstream << " " << easytimer::time_rest<easytimer::nanoseconds>(t.time_since_epoch()).count();

        return sstream.str();
    }

    static std::string get_time_string(const std::time_t t)
    {
        return get_time_string(
                easytimer::clock_type::from_time_t(t));
    }


    template <typename _Dur, typename _From>
    constexpr std::chrono::time_point<typename _From::clock, _Dur> time_point_cast(const _From src_time_point) noexcept
    {
        using duration = std::chrono::duration<typename _Dur::rep, typename _Dur::period>;
        return std::chrono::time_point_cast<duration, typename _From::clock, typename _From::duration>(src_time_point);
    }

  
}


#endif //GAMEINTERFACE_TIME_H

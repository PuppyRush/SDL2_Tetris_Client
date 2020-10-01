//
// Created by chaed on 19. 2. 28.
//

#ifndef SDL2_TETRIS_SERVER_TOOL_TIMER_H
#define SDL2_TETRIS_SERVER_TOOL_TIMER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <thread>
#include <numeric>
#include <atomic>
#include <vector>
#include <string>
#include <iomanip>
#include <ratio>

#include <boost/serialization/singleton.hpp>

#include "Times.h"
//#include "TypeTraits.h"

//countdown, schedueling, elaspedtime, stopwatch

//countdown - 일정 시간후 / 특정시간에 호출.
//schedueling - 특정 조건에 맞게 호출.
//elapsedtime - 시작과 끝 점 측정하기.
//stopwatch - 호출때마다 기록 누적하기.

#undef min
#undef max

namespace easytimer {

    
using t_timer = short;
const t_timer TIMER_MIN = std::numeric_limits<t_timer>::min();
const t_timer TIMER_MAX = std::numeric_limits<t_timer>::max();

template<typename _Per, typename _Rep = easytimer::clock_type::rep, typename _Cl = easytimer::clock_type>
struct _Tm {
    using rep = _Rep;
    using clock_type = _Cl;
    using precision = _Per;
    //using precision = period; //std::ratio_multiply<std::ratio<_XTIME_NSECS_PER_TICK, 1>, period>;
    using duration = std::chrono::duration<rep, precision>;
    using time_point = std::chrono::time_point<clock_type, duration>;
};

template <typename _Per, typename _Rep = long long>
struct TimerSet
{
public:
    typename _Tm<_Per, _Rep>::time_point startPoint;
    typename _Tm<_Per, _Rep>::time_point endPoint;
    typename _Tm<_Per, _Rep>::duration duration;
};


template <typename T, typename _Rep>
inline static T get_duration(const TimerSet<_Rep>& set) noexcept
{
    return std::chrono::duration_cast<T>(set.startPoint - set.endPoint);
}

template <typename T, typename _Rep>
inline static T get_duration(TimerSet<_Rep>&& set) noexcept
{
    return std::chrono::duration_cast<T>(set.startPoint - set.endPoint);
}


//시간단위 , 범위
template<typename _Rep, typename _Rn = long long>
class TimerBasic : private boost::serialization::singleton<TimerBasic<_Rep, _Rn>>
{
public:

    friend class boost::serialization::singleton<TimerBasic>;

    using precision = _Rep;
    using range = _Rn;
    using time_type = _Tm<precision, range>;
    using duration = typename time_type::duration;
    using clock_type = typename time_type::clock_type;
    using time_point = typename time_type::time_point;

    constexpr time_point now() noexcept
    {
        if constexpr (std::is_same< typename easytimer::clock_type::time_point, time_point>::value)
        {
            return clock_type::now();
        }
        else
        {
           return  std::chrono::time_point_cast<duration, clock_type, typename clock_type::duration>(clock_type::now());
        }
    }

    void start() noexcept
    {
        m_timeset.startPoint = now();
    }

    void end()
    {
        m_timeset.endPoint = now();
        _cal_duration();
    }

    void suspend() noexcept
    {
        m_suspendPoint = now();
        m_isSuspeded = true;
    }

    void resume()
    {
        m_suspendedDuration += (duration{ now() - m_suspendPoint });
        m_isSuspeded = false;
        m_suspendCount++;
    }

    void reset()
    {
        m_timeset.startPoint = now();
        m_timeset.endPoint = time_point{};
        m_suspendedDuration = { 0 };
        m_suspendCount = { 0 };
        m_isSuspeded = false;
    }

    inline time_point start_point() noexcept
    {
        return m_timeset.startPoint;
    }

    inline time_point end_point() noexcept
    {
        return m_timeset.endPoint;
    }

    duration time_duration() noexcept
    {
        return time_point::duration(end_point() - start_point());
    }

    constexpr hours hour() noexcept
    {
        return std::chrono::duration_cast<hours>(end_point() - start_point());
    }

    constexpr minutes minute() noexcept
    {
        return std::chrono::duration_cast<minutes>(end_point() - start_point());
    }

    constexpr seconds second() noexcept
    {
        return std::chrono::duration_cast<seconds>(end_point() - start_point());
    }

    constexpr milliseconds millisecond() noexcept
    {
        return std::chrono::duration_cast<milliseconds>(end_point() - start_point());
    }

    constexpr microseconds microsecond() noexcept
    {
        return std::chrono::duration_cast<microseconds>(end_point() - start_point());
    }

    constexpr nanoseconds nanosecond() noexcept
    {
        return std::chrono::duration_cast<nanoseconds>(end_point() - start_point());
    }

    auto suspended_count()
    {
        return m_suspendedDuration.size();
    }

protected:

    TimerSet<precision> M_DEFAULT_TIME{ time_point{}, time_point{} };

    TimerSet<precision>& m_timeset{ M_DEFAULT_TIME };
    time_point m_suspendPoint;
    duration m_suspendedDuration{ 0 };
    size_t m_suspendCount{ 0 };
    bool m_isSuspeded{ false };

    TimerBasic()
        :m_timeset(M_DEFAULT_TIME)
    {
        m_timeset.startPoint = now();
    }

    TimerBasic(TimerSet<precision>& set)
        :m_timeset(set)
    {}

    virtual ~TimerBasic() = default;

    void _cal_duration()
    {
        m_timeset.duration = easytimer::get_duration<decltype(m_timeset.duration), precision>(m_timeset);
        
        //if (m_isSuspeded)
        //    m_suspendedDuration += (time_point::duration { now() - m_suspendPoint });

        if (m_suspendedDuration > duration{ 0 })
        {
            m_timeset.duration -= m_suspendedDuration;
        }
    }
};


}

#endif //SDL2_TETRIS_SERVER_TOOL_TIMER_H

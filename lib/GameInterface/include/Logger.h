//
// Created by chaed on 19. 8. 8..
//

#ifndef GAMEINTERFACE_LOGGER_H
#define GAMEINTERFACE_LOGGER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#define __NOOP ;

#include <string>
#include <string_view>

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "EasyTimer/Times.h"

namespace game_interface::logger {

class Logger : private boost::noncopyable, boost::serialization::singleton<Logger>
{
public:
    friend class boost::serialization::singleton<Logger>;

    enum class logger_level
    {
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
        None
    };

    inline static Logger& getInstance()
    {
        static Logger logger;
        return logger;
    }

    void printLog(const char* str, const logger_level& lv)
    {
       // #ifdef SEG_DEBUG
       printf("[%s][%s]:%s\n", easytimer::get_time_string(easytimer::clock_type::now()).c_str(), getLevelString(lv).data(), str);
       // #else
        __NOOP
       // #endif
    }

    void printLog(const std::string& str, const logger_level& lv)
    {
        //#ifdef SEG_DEBUG
        printLog(str.c_str(), lv);
        //#else
        __NOOP
        //#endif
    }

private:

    Logger() = default;

    ~Logger() = default;

    const std::string_view m_fatal = std::string_view("Fatal");
    const std::string_view m_error = std::string_view("Error");
    const std::string_view m_warning = std::string_view("Warning");
    const std::string_view m_info = std::string_view("Info");
    const std::string_view m_debug = std::string_view("Debug");
    const std::string_view m_none = std::string_view("None");

    inline const std::string_view getLevelString(const logger_level& lv) const noexcept
    {
        switch (lv) {
            case logger_level::Fatal:
                return m_fatal;
            case logger_level::Error:
                return m_error;
            case logger_level::Warning:
                return m_warning;
            case logger_level::Info:
                return m_info;
            case logger_level::Debug:
                return m_debug;
            default:
                assert(0);
                return m_none;
                break;
        }
    }


};

}

#endif //SDL2_TETRIS_CLIENT_SEG_LOGGER_H

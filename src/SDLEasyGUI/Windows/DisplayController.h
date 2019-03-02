//
// Created by chaed on 18. 12. 15.
//

#ifndef GUI_GAMECONTROLLER_H
#define GUI_GAMECONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <unordered_map>
#include <queue>
#include <thread>
#include <condition_variable>
#include <boost/serialization/singleton.hpp>

#include "SDLEasyGUI/SEG_Type.h"
#include "../SEG_Resource.h"
#include "DisplayInterface.h"

namespace sdleasygui {

/*

namespace std
{
template<>
struct hash<DisplayInfo>
{
    size_t operator()(const DisplayInfo& obj) const
    {
        using modeType = underlying_type_t <TLocalMode>;
        using dpType = underlying_type_t <TDisplay >;
        using dpModeType = underlying_type_t <TDisplayMode >;
        const auto mode = static_cast<modeType>(obj.mode);
        const auto dp = static_cast<dpType>(obj.display);
        const auto dpMode = static_cast<dpType>(obj.displayMode);
        return hash<modeType>()(mode)*13 + hash<modeType>()(dp)*21 * hash<dpModeType>()(dpMode)*37 * obj.id*53;
    }
};
}*/

using controll_map_key = std::pair<game_interface::t_id, game_interface::t_id>;
struct KeyHash {
    std::size_t operator()(const controll_map_key &obj) const {
        return std::hash<game_interface::t_id>()(obj.first) * 13 + std::hash<game_interface::t_id>()(obj.second) * 21;
    }
};

struct KeyEqual {
    bool operator()(const controll_map_key &lhs, const controll_map_key &rhs) const {
        return rhs.first == lhs.first &&
            rhs.second == rhs.second;
    }
};

class DisplayController : public boost::serialization::singleton<DisplayController>
{

public:
    using display_ptr = DisplayInterface *;
    using modal_ary = std::deque<display_ptr>;
    using modaless_ary =  std::vector<display_ptr>;
    using modaless_ary_iterator = modaless_ary::const_iterator;

    void run();

    void modal_open(display_ptr);
    void modal_close();
    void modaless(display_ptr);
    void close(const game_interface::t_id id);
    void refreshModal();

    static std::shared_ptr<DisplayController> getInstance();

private:

    DisplayController();

    game_interface::t_id getActivatedWindowID(const SDL_Event *event);
    display_ptr findFromId(const game_interface::t_id id);

    void _release();
    void _pumpEvent();

    template<class T>
    display_ptr _find(const T &ary, const game_interface::t_id id);

    modaless_ary m_modalessAry;
    modal_ary m_modalStack;

    std::thread m_thread;
    std::atomic_bool m_run = true;
    std::condition_variable m_modalAryCV;
    std::mutex m_modalAryMutex;
};

struct modal_opener {
    explicit modal_opener(DisplayController::display_ptr display) {
        DisplayController::getInstance()->modal_open(display);
    }

    ~modal_opener() {
        DisplayController::getInstance()->modal_close();
    }

};

}

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H

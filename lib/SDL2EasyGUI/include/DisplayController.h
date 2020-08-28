//
// Created by chaed on 18. 12. 15.
//

#ifndef GUI_GAMECONTROLLER_H
#define GUI_GAMECONTROLLER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <memory>
#include <unordered_map>
#include <deque>
#include <map>
#include <thread>
#include <condition_variable>

#include <boost/serialization/singleton.hpp>

#include "SDL2EasyGUI/include/SEG_Type.h"
#include "SDL2EasyGUI/include/SEG_Resource.h"
#include "SDL2EasyGUI/include/DisplayInterface.h"

namespace seg {

using controll_map_key = std::pair<t_id, t_id>;

struct KeyHash
{
    std::size_t operator()(const controll_map_key& obj) const
    {
        return std::hash<t_id>()(obj.first) * 13 + std::hash<t_id>()(obj.second) * 21;
    }
};

struct KeyEqual
{
    bool operator()(const controll_map_key& lhs, const controll_map_key& rhs) const
    {
        return rhs.first == lhs.first &&
               rhs.second == rhs.second;
    }
};

class DisplayMap : private boost::serialization::singleton<DisplayMap>
{
public:
    using display_type = DisplayInterface;
    using unique_type = display_type::unique_type;
    using display_ptr = std::shared_ptr<display_type>;
    using alert_ary = std::deque<display_type*>;
    using modal_ary = std::unordered_multimap<t_id, std::deque<display_ptr>>;
    using modaless_ary = std::unordered_multimap<t_id, display_ptr>;
    using modaless_ary_iterator = modaless_ary::const_iterator;

    friend class boost::serialization::singleton<DisplayMap>;


    void pushModal(display_ptr dp) {

        //modaless에 부모display가 없다면 
    }
    display_ptr popModal() {

    }

    void addModaless(display_ptr dp) {

    }
    display_ptr eraseModaless(t_id uniqueId) {

    }

private:

    DisplayMap()
    {

    }

    //key는 display_ptr의 unique_id
    std::map<unique_type, display_ptr> m_modalessMap;

    //key는 부모 display의 uniqueid
    std::unordered_multimap<unique_type, std::deque<display_ptr>> m_modalmap;

};

class DisplayController : private boost::serialization::singleton<DisplayController>
{

public:
    using display_type = DisplayInterface;
    using display_ptr = std::shared_ptr<display_type>;
    using alert_ary = std::deque<display_type*>;

    friend class boost::serialization::singleton<DisplayController>;

	DisplayController();

    virtual ~DisplayController();

	void run();

    void finish();

    void alert(display_type*);

    void alert_close();

    void modal_open(display_ptr);

    void modal_close();

    void modaless_open(display_ptr);

    void modaless_close(seg::t_id winid);

    void close(const t_id id);

    void refreshModal();

    void getDisplay(const t_id displayId);

    void setMainDisplay(const display_ptr dp);

    void startMainDisplay();

    static DisplayController& getInstance()
    {
        return boost::serialization::singleton<DisplayController>::get_mutable_instance();
    }

    inline bool isRunningDisplay()
    { return !(m_modalessAry.empty() && m_modalStack.empty()); }

private:

    t_id getActivatedWindowID(const SDL_Event* event);

    display_ptr findFromId(const t_id id);

    void _open(display_ptr display);

    void _release();

    void _pumpEvent();

    void _modal();
    void _modaless();

    template<class T>
    display_ptr _find(const T& ary, const t_id id);

    DisplayMap m_displayMap;
    alert_ary m_alertAry;

    std::thread m_thread;
    std::atomic_bool m_run = true;
    std::condition_variable m_modalAryCV;
    std::mutex m_modalAryMutex;
    std::condition_variable m_mainDisplayChangeCv;
    std::mutex m_mainDisplayChangeMutex;

    display_ptr m_mainDp;
};

struct modal_opener
{

    DisplayController::display_ptr display;

    explicit modal_opener(DisplayController::display_ptr display)
            : display(display)
    {
        DisplayController::getInstance().modal_open(display);
    }

    ~modal_opener()
    {
        DisplayController::getInstance().modal_close();
    }

};

}

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
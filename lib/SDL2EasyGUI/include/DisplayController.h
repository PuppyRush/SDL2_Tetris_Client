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
#include <list>
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

class DisplayController : private boost::serialization::singleton<DisplayController>
{

public:
    using display_type = DisplayInterface;
    using display_ptr = std::shared_ptr<display_type>;
    using alert_ary = std::list<display_type*>;
    using modal_ary = std::deque<display_ptr>;
    using modaless_ary =  std::list< modal_ary>;
    using modaless_ary_iterator = modaless_ary::const_iterator;

    friend class boost::serialization::singleton<DisplayController>;

	DisplayController();

    virtual ~DisplayController();

	void run();

    void finish();

    void alert(display_type*);

    void alert_close();

    template <typename _Display, typename... _Args>
    static display_ptr modal_open(_Args&& ... __args)
    {
       std::shared_ptr<DisplayInterface> display = std::make_shared<_Display>(std::forward<_Args>(__args)...);
        
       DisplayController::getInstance().getModalStack().push_back(display);
       //m_modalAryCV.notify_one();

        DisplayController::getInstance()._postOpenDisplay(display);

        display->modal();
        
        return display;
    }

    void modal_close();

    template <typename _Display>
    static void modaless_open()
    {
        auto display = std::make_shared<_Display>();

        modal_ary s;
        s.push_back(display);
        DisplayController::getInstance().getModalessList().push_back(s);
       // m_modalAryCV.notify_one();

        DisplayController::getInstance()._postOpenDisplay(display);

        display->modaless();

    }


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

    inline modal_ary& getModalStack() noexcept { return m_modalStack; }
    
    inline modaless_ary& getModalessList() noexcept { return m_modalessAry; }

private:

    t_id getActivatedWindowID(const SDL_Event* event);

    display_ptr findFromId(const t_id id);

    void _preModalOpen(display_ptr display);

    void _postOpenDisplay(display_ptr display);

    void _release();

    void _pumpEvent();

    template<class T>
    display_ptr _find(const T ary, const t_id id);

    modaless_ary m_modalessAry;
    modal_ary m_modalStack;
    alert_ary m_alertAry;

    std::thread m_thread;
    std::atomic_bool m_run = true;
    std::condition_variable m_modalAryCV;
    std::mutex m_modalAryMutex;
    std::condition_variable m_mainDisplayChangeCv;
    std::mutex m_mainDisplayChangeMutex;

    display_ptr m_mainDp;
};

}

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
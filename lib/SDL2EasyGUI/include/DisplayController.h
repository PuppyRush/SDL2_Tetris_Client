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
#include <algorithm>

#include <boost/serialization/singleton.hpp>

#include "EventQueue.h"
#include "SEG_Type.h"
#include "SEG_Resource.h"
#include "DisplayInterface.h"

namespace seg {

class DisplayMap : private boost::serialization::singleton<DisplayMap>
{
public:
    using display_type = DisplayInterface;
    using unique_type = display_type::unique_type;
    using display_ptr = std::shared_ptr<display_type>;
    using alert_ary = std::deque<display_type*>;
    using modal_ary = std::unordered_map<unique_type, std::deque<display_ptr>>;
    using modaless_ary = std::map<unique_type, display_ptr>;

    friend class boost::serialization::singleton<DisplayMap>;

    void initialize(display_ptr dp)
    {
        if (dp == nullptr)
        {
            assert(0);
            return;
        }
        if (dp->getSuperWindowID() != SUPER_WINDOWS_ID)
        {
            assert(0);
            dp->setSuperWindowID(SUPER_WINDOWS_ID);
        }

        modal_ary::mapped_type q;
        q.push_back(dp);
        m_modalmap.insert({ dp->getSuperWindowID(), q });
    }

    bool exist(const unique_type uniqueId)
    {
        return find(uniqueId) != nullptr;
    }

    bool exist(const display_ptr& dp)
    {
        return find(dp) != nullptr;
    }

    display_ptr find(const unique_type uniqueId)
    {
        for (const auto& _q : m_modalmap)
        {
            for (const auto& _dp : _q.second)
            {
                if (_dp->compareUnique(uniqueId))
                    return _dp;
            }
        }

        if (m_modalessMap.empty() == false && m_modalessMap.contains(uniqueId))
        {
            return m_modalessMap.at(uniqueId);
        }

        return nullptr;
    }

    display_ptr find( const display_ptr& dp)
    {
        if (m_modalmap.contains(dp->getSuperWindowID()))
        {
            const auto& q = m_modalmap.at(dp->getSuperWindowID());
            for (auto _dp : q)
            {
                if (dp->compareUnique(_dp->getWindowID()))
                    return _dp;
            }
        }

        if (m_modalessMap.contains(dp->getWindowID()))
        {
            return m_modalessMap.at(dp->getWindowID());
        }

        return nullptr;
    }

    void pushModal(display_ptr dp) 
    {
        if (m_modalmap.contains(dp->getSuperWindowID()))
        {
            auto& q = m_modalmap.at(dp->getSuperWindowID());
            auto it = std::find_if(std::begin(q), std::end(q), [&](const display_ptr& _dp){
                return _dp->compareUnique(dp->getWindowID());
            });

            //이미 존재하는 display
            if (it != q.end())
            {
                assert(0);
            }

            q.push_back(dp);
        }
        else
        {
            modal_ary::mapped_type q;
            q.push_back(dp);
            m_modalmap.insert({ dp->getSuperWindowID(), q });
        }
    }

    display_ptr popModal(const unique_type superParentId) 
    {
        if (m_modalmap.empty())
        {
            return nullptr;
        }
        else if (m_modalmap.contains(superParentId) == false)
        {
            return nullptr;
        }

        auto& q = m_modalmap.at(superParentId);
        if (q.empty())
        {
            return nullptr;
        }
        else
        {
            auto dp = q.back();
            q.pop_back();
            return dp;
        }
            
    }

    void addModaless(display_ptr dp) 
    {
        if (m_modalessMap.contains(dp->getWindowID()) == true)
        {
            //이미 존재하는 display
            assert(0);
        }
        else
        {
            m_modalessMap.insert({ dp->getWindowID(), dp });
        }
    }

    display_ptr eraseModaless(t_id uniqueId) 
    {
        if (m_modalessMap.contains(uniqueId) == false)
        {
            assert(0);
            return nullptr;
        }
        else
        {
            auto dp = m_modalessMap.at(uniqueId);
            m_modalessMap.erase(uniqueId);
            return dp;
        }
    }



    static DisplayMap& getInstance()
    {
        return boost::serialization::singleton<DisplayMap>::get_mutable_instance();
    }

    DisplayMap() = default;
private:

    //key는 display_ptr의 unique_id
    modaless_ary m_modalessMap;

    //key는 부모 display의 uniqueid
    modal_ary m_modalmap;

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

    template <typename _Display, typename... _Args>
    static display_ptr modal_open(_Args&& ... __args)
    {
        display_ptr display = std::make_shared<_Display>(std::forward<_Args>(__args)...);
        DisplayMap::getInstance().pushModal(display);
        DisplayController::getInstance().getDisplayEventQueue().pushEvent(display);
        
        return display;
    }

    void modal_close(const display_ptr& dp);

    template <typename _Display, typename... _Args>
    static display_ptr modaless_open(_Args&& ... __args)
    {
        display_ptr display = std::make_shared<_Display>(std::forward<_Args>(__args)...);
        DisplayMap::getInstance().addModaless(display);
        DisplayController::getInstance().getDisplayEventQueue().pushEvent(display);

        return display;
    }

    void modaless_close(display_type::unique_type uniqueId);

    void _preModalOpen(display_ptr display);

    void _postOpenDisplay(display_ptr display);

    //void close(const display_ptr id);

    void refreshModal();

    void getDisplay(const t_id displayId);

    void setMainDisplay(const display_ptr dp);

    void startMainDisplay();

    static DisplayController& getInstance()
    {
        return boost::serialization::singleton<DisplayController>::get_mutable_instance();
    }

private:

    t_id getActivatedWindowID(const SDL_Event* event);

    void _open(display_ptr display);
    void _release();
    void _pumpEvent();


    void _modal();
    void _modaless();

    EventQueue<display_ptr>& getDisplayEventQueue()
    {
        return m_newDisplayQ;
    }

    template<class T>
    display_ptr _find(const T& ary, const t_id id);

    alert_ary m_alertAry;

    std::thread m_thread;
    std::atomic_bool m_run = true;

    std::thread m_mainDpThread;

    std::condition_variable m_modalAryCV;
    std::mutex m_modalAryMutex;
    std::condition_variable m_mainDisplayChangeCv;
    std::mutex m_mainDisplayChangeMutex;

    display_ptr m_mainDp;

    EventQueue<display_ptr> m_newDisplayQ;
};

//struct modal_opener
//{
//
//    DisplayController::display_ptr display;
//
//    explicit modal_opener(DisplayController::display_ptr display)
//            : display(display)
//    {
//        DisplayController::getInstance().modal_open(display);
//    }
//
//    ~modal_opener()
//    {
//        DisplayController::getInstance().modal_close();
//    }
//
//};

}

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H
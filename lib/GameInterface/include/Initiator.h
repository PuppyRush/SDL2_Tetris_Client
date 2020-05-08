//
// Created by chaed on 19. 5. 4.
//

#ifndef SDL2_TETIRS_CLIENT_INITIATOR_H
#define SDL2_TETIRS_CLIENT_INITIATOR_H

#include <ace/Init_ACE.h>

#include "Constant.h"
#include "PacketQueue.h"
#include "Room.h"

#include "ScopeTimer.h"
#include "ElapsedTimer.h"
#include "Stopwatch.h"
#include "Countdown.h"
#include "Scheduling.h"

namespace game_interface {
    
static void callback(void*)
{
    std::cout << "call!" << time::get_time_string(time::now_to_time()) << std::endl;
}   

static void cal_time()
{
    time::TimerSet< std::nano> set;
    time::ElapsedTimer<std::milli> el;
    {
        //el.start();
        //time::ScopeTimer<std::nano> t(set);
        //for (int i = 0; i < 500; i++)
        //   // std::cout << "a";
        //el.end();

        //auto h = el.hour();
        //auto m = el.minute();
        //auto s = el.second();
        //auto mili = el.millisecond();
    }

    int* b = new int{ 3 };
    {
        /*time::Countdown<std::nano> cd{ &callback, b, { 0,0,3,700 } };
        cd.start();
        Sleep(2000);
        cd.suspend();
        Sleep(3000);
        cd.resume();
        cd.join();*/
    }
    {
       // auto t = time::clock_type::now() + time::seconds{ 6 };
       // time::Countdown<std::nano> cd{ &callback, (void*) b, t };
       // cd.start();
       // //Sleep(2000);
       // //cd.stop();
       // cd.suspend();
       //// Sleep(3000);
       // cd.resume();
       // cd.join();
    }
    {
        #include <boost/date_time/gregorian/greg_date.hpp>
        #include "boost/date_time/posix_time/posix_time.hpp"

        /*time::SchedulingBuilder bld{ {2020,boost::gregorian::May,7} };
        bld.hour(23);
        bld.minute(02);
        time::Scheduling sch(&callback, b, bld);
        sch.start();
        */

        time::SchedulingBuilderDaily bld{ {2020,boost::gregorian::May,8} ,1, 2};
        bld.hour(0);
        bld.minute(50);
        time::Scheduling sch(&callback, b, bld);
        sch.start();
    }
    //auto until_time = time::clock_type::now();
    //until_time += time::seconds{ 1 };
    //time::Countdown<std::milli> countdown{ &callback, until_time };
    //countdown.start();

    //time::Stopwatch<std::nano> a;
    //{
    //    a.start();

    //    std::cout << time::get_time_string(std::chrono::system_clock::now()) << std::endl;
    //    std::this_thread::sleep_for(time::milliseconds{ 1800 });
    //    std::this_thread::sleep_for(time::nanoseconds{ 500 });
    //    std::this_thread::sleep_for(time::seconds{ 2 });
    //    a.do_record();
    //    std::cout << time::get_time_string(std::chrono::system_clock::now());

    //    std::this_thread::sleep_for(time::milliseconds{ 2230 });

    //    a.do_record();

    //    std::this_thread::sleep_for(time::milliseconds{ 1700 });

    //    a.suspend();
    //    std::this_thread::sleep_for(time::milliseconds{ 500 });
    //    a.resume();

    //    a.do_record();

    //    Sleep(1300);

    //    a.do_record();
    //}
}

static void GameInterface_Init(bool isServer)
{
    ACE::init();

    g_isServer = isServer;

    if (isServer) {
        g_modulename = NAME_SERVER;
    } else {
        g_modulename = NAME_CLIENT;
    }

    PacketQueue::getInstance().run();

    atomic::Atomic<Room>::getInstance().setFirstUnique(SERVER_ATOMIC_START);

    cal_time();
    
}

}

#endif //SDL2_TETIRS_CLIENT_INITIATOR_H

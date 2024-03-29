//
// Created by chaed on 19. 5. 4.
//

#ifndef GAMEINTERFACE_INITIATOR_H
#define GAMEINTERFACE_INITIATOR_H

#include <ace/Init_ACE.h>

#include <SimpleIni.h>

#include "Constant.h"
#include "PacketQueue.h"
#include "Room.h"

#include "EasyTimer/ScopeTimer.h"
#include "EasyTimer/ElapsedTimer.h"
#include "EasyTimer/Stopwatch.h"
#include "EasyTimer/Countdown.h"
#include "EasyTimer/Scheduling.h"

namespace game_interface {
    
static void callback(void*)
{
    std::cout << "call!" << easytimer::get_time_string(easytimer::now_to_time()) << std::endl;
}   

static void cal_time()
{
    easytimer::TimerSet< std::nano> set;
    easytimer::ElapsedTimer<std::milli> el;
    {
        //el.start();
        //easytimer::ScopeTimer<std::nano> t(set);
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
        /*easytimer::Countdown<std::nano> cd{ &callback, b, { 0,0,3,700 } };
        cd.start();
        Sleep(2000);
        cd.suspend();
        Sleep(3000);
        cd.resume();
        cd.join();*/
    }
    {
       // auto t = easytimer::clock_type::now() + easytimer::seconds{ 6 };
       // easytimer::Countdown<std::nano> cd{ &callback, (void*) b, t };
       // cd.start();
       // //Sleep(2000);
       // //cd.stop();
       // cd.suspend();
       //// Sleep(3000);
       // cd.resume();
       // cd.join();
    }
    #include <boost/date_time/gregorian/greg_date.hpp>
    #include "boost/date_time/posix_time/posix_time.hpp"
    {
        /*easytimer::SchedulingBuilder bld{ {2020,boost::gregorian::May,7} };
        bld.hour(23);
        bld.minute(02);
        easytimer::Scheduling sch(&callback, b, bld);
        sch.start();
        */

        easytimer::SchedulingBuilderDaily bld{ {2020,boost::gregorian::May,11} ,1, 2};
        bld.hour(21);
        bld.minute(30);
        easytimer::Scheduling sch(&callback, b, bld);
        sch.start();
    }

    {
        easytimer::SchedulingBuilderManually bld{  {{ 2020,boost::gregorian::May,12},12,3,4 } };
        bld.addTimepoint( {{ 2020,boost::gregorian::May,12 }, 4, 5, 1 });
        bld.addTimepoint({ { 2020,boost::gregorian::Dec,30 }, 22, 5, 1 });
        bld.addTimepoint({ { 2020,boost::gregorian::Jan,21 }, 22, 5, 1 });
        easytimer::Scheduling sch(&callback, b, bld);
        sch.start();
    }

    {
        easytimer::SchedulingBuilderWeekly bld{ {2020,boost::gregorian::May,26} , 2 };
        bld.hour(23);
        bld.minute(30);
        bld.second(55);
        bld.addWeekdays(easytimer::SchedulingBuilderWeekly::weekdays::Sunday);
        bld.addWeekdays(easytimer::SchedulingBuilderWeekly::weekdays::Monday);
        bld.addWeekdays(easytimer::SchedulingBuilderWeekly::weekdays::Wednesday);
        bld.addWeekdays(easytimer::SchedulingBuilderWeekly::weekdays::Saturday);
        easytimer::Scheduling sch(&callback, b, bld);
        sch.start();
    }
    //auto until_time = easytimer::clock_type::now();
    //until_time += easytimer::seconds{ 1 };
    //easytimer::Countdown<std::milli> countdown{ &callback, until_time };
    //countdown.start();

    easytimer::Stopwatch<std::nano> a;
    {
        a.start();

        std::cout << easytimer::get_time_string(std::chrono::system_clock::now()) << std::endl;
        std::this_thread::sleep_for(easytimer::milliseconds{ 1800 });
        std::this_thread::sleep_for(easytimer::nanoseconds{ 500 });
        std::this_thread::sleep_for(easytimer::seconds{ 2 });
        a.do_record();
        std::cout << easytimer::get_time_string(std::chrono::system_clock::now());

        std::this_thread::sleep_for(easytimer::milliseconds{ 2230 });

        a.do_record();

        std::this_thread::sleep_for(easytimer::milliseconds{ 1700 });

        a.suspend();
        std::this_thread::sleep_for(easytimer::milliseconds{ 500 });
        a.resume();

        a.do_record();

        Sleep(1300);

        a.do_record();
    }
}

static void ReadIni()
{
    CSimpleIni ini;
    ini.LoadFile(NAME_OPTION_FILE.data());

    std::string ip{ ini.GetValue(NAME_SECTION_SERVERINFO.data(), NAME_SERVERINFO_IP.data(), NAME_SERVERINFO_IP_DEFAULT.data()) };
    std::string port{ ini.GetValue(NAME_SECTION_SERVERINFO.data(), NAME_SERVERINFO_PORT.data(), NAME_SERVERINFO_PORT_DEFAULT.data()) };
}

static void GameInterface_Init(bool isServer)
{
    ACE::init();
    ReadIni();

    g_isServer = isServer;

    if (isServer) {
        g_modulename = NAME_SERVER;
    } else {
        g_modulename = NAME_CLIENT;
    }

    PacketQueue::getInstance().run();

    //game_interface::atomic::Atomic<Room>::getInstance().setFirstUnique(SERVER_ATOMIC_START);

    //cal_time();
    
}

}

#endif //SDL2_TETIRS_CLIENT_INITIATOR_H

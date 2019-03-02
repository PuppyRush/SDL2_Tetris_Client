//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "TWaitingRoomDisplay.h"
#include "TWaitingRoomCard.h"
#include "SDLEasyGUI/Controller/ListBox.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/Controller/EditLabel.h"
#include "SDLEasyGUI/SEG_TypeTraits.h"
#include "../../Common/TResource.h"

SDL_TETRIS

using namespace std;
using namespace sdleasygui;
using namespace game_interface;

void TWaitingRoomDisplay::registerEvent()
{
   // event_buttonClick(toUType(resource::MAIN_MULTI_GAME_START_BUTTON), std::bind(&TWaitingRoomDisplay::onClickedEnterServer, this));
   // event_buttonClick(toUType(resource::MAIN_OPTION_BUTTON), std::bind(&TWaitingRoomDisplay::onClickedOption, this));
}

void TWaitingRoomDisplay::onPreInitialize() {

    {
        ListBoxBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 9, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM))->
            width(m_chatBoxBeginWidth)->
            height(m_chatBoxBeginHeight)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        EditLabelBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y + m_chatBoxBeginHeight}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 9, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM))->
            width(m_chatBoxBeginWidth)->
            height(30)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ListBoxBuilder bld(getWindow(), {m_userBoxBeginPoint.x, m_userBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 9, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM))->
            width(m_userBoxBeginWidth)->
            height(m_userBoxBeginHeight)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y}, "CREATE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM))->
            width(m_createBtnBeginWidth)->
            height(m_createBtnBeginHeight)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

          addControll(bld.build());
    }

    DisplayInterface::onPreInitialize();
}

void TWaitingRoomDisplay::onDraw() {
    DisplayInterface::onDraw();
}

void TWaitingRoomDisplay::updateObserver(const Packet& packet)
{
    switch(packet.getHeader().message)
    {
        case messageInfo::WAITINGROOMS_INIT_INFO_ROOMS:
            recvInitRoomInfo(packet);
            break;
        case messageInfo::WAITINGROOMS_INIT_INFO_PLAYERS:
            recvInitPlayerInfo(packet);
            break;
    }
}

void TWaitingRoomDisplay::recvInitRoomInfo(const game_interface::Packet &packet)
{
    t_size begin_x = WINDOW_WIDTH/3;
    t_size begin_y = WINDOW_HEIGHT/3;

    const Json::Value root = packet.getPayload();
    const int count = root["count"].asInt();

    for(int i=0 ; i < count ; ++i)
    {
        string roomname = "room";
        roomname += to_string(i);

        const Json::Value jsonroom = root[roomname];
        string name  = jsonroom["name"].asString();
        int number = jsonroom["number"].asInt();
        int unique = jsonroom["unique"].asInt();
        t_time time =  atoll(jsonroom["time"].asCString());


        TWaitingRoomCardBuilder bld(getWindow(), {begin_x, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM))->
            width(200)->
            height(200)->
            borderColor(ColorCode::white)->
            borderThick(3)->
            enabled(true);

        addControll(bld.build());

    }

}

void TWaitingRoomDisplay::recvInitPlayerInfo(const game_interface::Packet& packet)
{
    const Json::Value root = packet.getPayload();
    const int count = root["count"].asInt();

    for(int i=0 ; i < count ; ++i) {
        string plyname = "player";
        plyname += to_string(i);

        const Json::Value jsonply = root[plyname];
        string name  = jsonply["name"].asString();
        int unique = jsonply["unique"].asInt();
        t_time time =  atoll(jsonply["time"].asCString());
    }
}


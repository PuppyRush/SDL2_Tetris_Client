//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "TWaitingRoomDisplay.h"
#include "TWaitingRoomCard.h"
#include "CreateGameroomWindow.h"

#include "SDL2EasyGUI/src/Controller/ListBox.h"
#include "SDL2EasyGUI/src/Controller/Button.h"
#include "SDL2EasyGUI/src/Controller/EditLabel.h"
#include "SDL2EasyGUI/src/SEG_TypeTraits.h"
#include "../../Common/TResource.h"
#include "../../TObject/TPlayer.h"
SDL_TETRIS

using namespace std;
using namespace sdleasygui;
using namespace game_interface;

void TWaitingRoomDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::WAITINGROOM_CREATE), &TWaitingRoomDisplay::createGameRoom, this);
    SEG_KEYDOWN(sdleasygui::toUType(resource::WAITINGROOM_CHAREDIT), &TWaitingRoomDisplay::enterChat, this);
}

void TWaitingRoomDisplay::postCreate()
{
    Packet packet{{getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_REQUEST_INIT_INFO}};
    TPlayer::getInstance()->sendPacket(packet);

    TDisplayInterface::postCreate();
}

void TWaitingRoomDisplay::onInitialize() {

    {
        ListBoxBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 11, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_CHATBOX))->
            width(m_chatBoxWidth)->
            height(m_chatBoxHeight)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        EditLabelBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y + m_chatBoxHeight+ 5}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 13, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_CHAREDIT))->
            width(m_chatBoxWidth)->
            height(30)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ListBoxBuilder bld(getWindow(), {m_userBoxBeginPoint.x, m_userBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 11, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(resource::WAITINGROOM_USERBOX))->
            width(m_userBoxWidth)->
            height(m_userBoxHeight)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y}, "CREATE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(resource::WAITINGROOM_CREATE))->
            width(m_btnWidth)->
            height(m_btnHeight)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

          addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y+m_btnHeight + 10}, "CREATE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(resource::WAITINGROOM_DISCONNECT))->
            width(m_btnWidth)->
            height(m_btnHeight)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onInitialize();
}

void TWaitingRoomDisplay::onDraw() {
    DisplayInterface::onDraw();
}

void TWaitingRoomDisplay::updateObserver(const Packet& packet)
{
    switch(packet.getHeader().message)
    {
        case messageInfo::WAITINGROOMS_REQUEST_INIT_INFO:
            recvGameRoomInfo(packet);
            break;
    }
    refresh();
}

void TWaitingRoomDisplay::recvGameRoomInfo(const game_interface::Packet &packet)
{
    t_size begin_x = m_controllBeginPoint.x;
    t_size begin_y = m_controllBeginPoint.y;

    const Json::Value root = packet.getPayload();
    const int count = root["gameroom_count"].asInt();

    for(int i=0 ; i < count ; ++i)
    {
        string roomname = "room";
        roomname += to_string(i);

        const Json::Value jsonroom = root[roomname];
        string name  = jsonroom["name"].asString();
        int number = jsonroom["number"].asInt();
        t_unique unique = jsonroom["unique"].asInt();
        t_time time =  atoll(jsonroom["time"].asCString());

        if(m_roomClickedFn.count(unique)>0)
            continue;

        const t_id resrouceId =sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM_BEGIN)+unique;

        TWaitingRoomCardBuilder bld(getWindow(), {begin_x, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::dimgray)->
            id( resrouceId )->
            width(200)->
            height(200)->
            borderColor(ColorCode::white)->
            borderThick(3)->
            enabled(true);

        m_roomClickedFn.insert(make_pair(unique, [this, unique](){

            Packet packet{{unique, getUnique(), messageInfo::WAITINGROOMS_REQUEST_ENTER}};
            TPlayer::getInstance()->sendPacket(packet);

        }));

        addControll(bld.build());
    }
}

void TWaitingRoomDisplay::recvInitPlayerInfo(const game_interface::Packet& packet)
{
    const Json::Value root = packet.getPayload();
    const int count = root["player_count"].asInt();
    const int wroom_unique = root["wroom_unique"].asInt();

    auto userBox = std::dynamic_pointer_cast<ListBox>(getControll(resource::WAITINGROOM_USERBOX));

    for(int i=0 ; i < count ; ++i) {
        string plyname = "player";
        plyname += to_string(i);

        const Json::Value jsonply = root[plyname];
        string name  = jsonply["name"].asString();
        t_unique unique = jsonply["unique"].asInt();
        t_time time =  atoll(jsonply["time"].asCString());

        userBox->appendItem(make_shared<UserInfo>(name,time,unique));
    }
}

void TWaitingRoomDisplay::createGameRoom()
{
    auto dlg = std::make_shared<CreateGameroomWindow>();
    dlg->setWindowHeight(250);
    dlg->setWindowWidth(350);
    auto res = dlg->modal();

    const string& roomname = dlg->m_roomname;

    Json::Value root;
    root["roomname"] = roomname;

    Packet packet{{getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_REQUEST_CREATE}, root};
    TPlayer::getInstance()->sendPacket(packet);

}


void TWaitingRoomDisplay::enterChat(const void* event)
{
    auto keyevent = static_cast<const SDL_KeyboardEvent*>(event);
    if(keyevent->keysym.sym == SDLK_RETURN)
    {
        const auto ctl = std::static_pointer_cast<EditLabel>(getControll(tetris::resource::WAITINGROOM_CHAREDIT));
        const auto chat = ctl->getString();

        Json::Value root;
        root["chat"] = chat;

        Packet packet{{getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_SEND_CHAT}, root};
        TPlayer::getInstance()->sendPacket(packet);

        ctl->clearString();
    }

}


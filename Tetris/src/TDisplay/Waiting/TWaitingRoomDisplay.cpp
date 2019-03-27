//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "TWaitingRoomDisplay.h"
#include "TWaitingRoomCard.h"
#include "TCreateGameroomWindow.h"
#include "../Game/TMultiGameRoomDisplay.h"

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
    SEG_KEYDOWN(sdleasygui::toUType(resource::WAITINGROOM_CHAREDIT), &TWaitingRoomDisplay::sendChat, this);
}

void TWaitingRoomDisplay::postCreate(TDisplayInterface::display_ptr display)
{
    Packet packet{{getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_REQUEST_INIT_INFO}};
    TPlayer::getInstance()->sendPacket(packet);

    TDisplayInterface::postCreate(display);
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
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y+m_btnHeight + 10}, "EXIT");
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
        case messageInfo::WAITINGROOMS_INIT_INFO_ROOMS_PLAYERS:
            recvGameRoomInfo(packet);
            break;
        case messageInfo ::WAITINGROOMS_RECV_CHAT:
            recvChat(packet);
            break;
        case messageInfo ::WAITINGROOMS_RESPONSE_CREATE:
            createGameroom(packet);
            break;
    }
    refresh();
}

void TWaitingRoomDisplay::recvGameRoomInfo(const game_interface::Packet &packet)
{
    t_size begin_x = m_controllBeginPoint.x;
    t_size begin_y = m_controllBeginPoint.y;

    const Json::Value root = packet.getPayload();

    const auto wroomname = root["name"].asString();
    const auto wroomunique = root["unique"].asUInt();

    m_waitingRoom.setUnique(wroomunique);
    m_waitingRoom.setRoomName(wroomname);

    const int roomCount = root["gameroom_count"].asInt();
    const Json::Value roomRoot = root[game_interface::NAME_GAMEROOM.data()];
    for(int i=0 ; i < roomCount ; ++i)
    {
        const Json::Value jsonroom = roomRoot[i];

        TGameRoom gameroom;
        gameroom.fromJson(jsonroom);

        //if(m_roomClickedFn.count(unique)>0)
        //    continue;

        //const t_id resrouceId =sdleasygui::toUType(resource::WAITINGROOM_GAMEROOM_BEGIN)+unique;

       /* TWaitingRoomCardBuilder bld(getWindow(), {begin_x, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::dimgray)->
            id( resrouceId )->
            width(200)->
            height(200)->
            borderColor(ColorCode::white)->
            borderThick(3)->
            enabled(true);
*/
        /*SEG_LBUTTONCLICK( resrouceId, [this, unique](void) ->void {

            Packet packet{{unique, this->getUnique(), messageInfo::WAITINGROOMS_REQUEST_ENTER}};
            TPlayer::getInstance()->sendPacket(packet);

        }, this);*/

        //addControll(bld.build());
    }

    const auto ctl = dynamic_cast<ListBox*>(getControll(tetris::resource::WAITINGROOM_USERBOX));

    const size_t plyCount = root["player_count"].asUInt();
    const Json::Value playerRoot = root[game_interface::NAME_PLAYER.data()];
    for(int i=0 ; i < plyCount ; ++i)
    {
        const Json::Value jsonPlayer = playerRoot[i];
        auto player = make_shared<TPlayer>();
        player->fromJson(jsonPlayer);

        ctl->appendItem(make_shared<UserInfo>(player->getUserName(),player->getMaketime(), player->getUnique()));
    }
}

void TWaitingRoomDisplay::createGameRoom()
{
    auto dlg = std::make_shared<TCreateGameroomWindow>();
    dlg->setWindowHeight(250);
    dlg->setWindowWidth(350);
    if(dlg->modal(dlg) == sdleasygui::resource ::BTN_OK)
    {
        const string& roomname = dlg->m_roomname;

        Json::Value root;
        root["name"] = roomname;

        Packet packet{{ m_waitingRoom.getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_REQUEST_CREATE}, root};
        TPlayer::getInstance()->sendPacket(packet);
    }
}


void TWaitingRoomDisplay::sendChat(const void *event)
{
    auto keyevent = static_cast<const SDL_KeyboardEvent*>(event);
    if(keyevent->keysym.sym == SDLK_RETURN)
    {
        const auto ctl = dynamic_cast<EditLabel*>(getControll(tetris::resource::WAITINGROOM_CHAREDIT));
        const auto chat = ctl->getString();

        Json::Value root;
        root["chat"] = chat;

        Packet packet{{m_waitingRoom.getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_SEND_CHAT}, root};
        TPlayer::getInstance()->sendPacket(packet);

        ctl->clearString();
    }

}

void TWaitingRoomDisplay::recvChat(const game_interface::Packet &packet)
{
    const string chat = packet.getPayload()["chat"].asString();
    const auto ctl = dynamic_cast<ListBox*>(getControll(tetris::resource::WAITINGROOM_CHATBOX));

    const string name{"Dd"};
    ctl->appendItem(make_shared<ChatInfo>(name,chat,packet.getHeader().timestamp));
}

void TWaitingRoomDisplay::createGameroom(const game_interface::Packet &packet){

    auto gameroom = make_shared<TMultiGameRoomDisplay>();
    gameroom->setWindowTitle("Tetris Game");
    gameroom->modal(gameroom);

}
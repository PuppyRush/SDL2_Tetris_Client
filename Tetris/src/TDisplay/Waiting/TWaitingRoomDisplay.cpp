//
// Created by chaed on 19. 2. 8.
//

#include <string>

#include "SDL2EasyGUI/include/ListBox.h"
#include "SDL2EasyGUI/include/Button.h"
#include "SDL2EasyGUI/include/EditLabel.h"
#include "SDL2EasyGUI/include/SEG_TypeTraits.h"

#include "TWaitingRoomDisplay.h"
#include "TWaitingRoomCard.h"
#include "TCreateGameroomDisplay.h"

#include "../Game/TMultiGameRoomDisplay.h"
#include "../../TObject/TPlayer.h"
#include "TResource.h"

SDL_TETRIS

using namespace std;
using namespace seg;
using namespace game_interface;
using namespace game_interface::packet;

TWaitingRoomDisplay::TWaitingRoomDisplay()
{
    
}

void TWaitingRoomDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::WAITINGROOM_CREATE),
                     &TWaitingRoomDisplay::onClickCreateGameRoom, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::WAITINGROOM_DISCONNECT),
                     &TWaitingRoomDisplay::onClickExit, this);
    SEG_KEYDOWN(seg::toUType(resource::WAITINGROOM_CHAREDIT), &TWaitingRoomDisplay::sendChat, this);
}

void TWaitingRoomDisplay::postCreate(TDisplayInterface::display_ptr display)
{
    Packet packet{{getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_REQUEST_INIT_INFO}};
    TPlayer::getInstance()->sendPacket(packet);

    TDisplayInterface::postCreate(display);
}

void TWaitingRoomDisplay::onInitialize()
{

	setWindowTitle("Hello Tetris World!");
	setBackgroundColor(ColorCode::black);
	setWindowHeight(800);

    {
        ListBoxBuilder bld(getWindow(), {m_gameroomBoxBeginPoint.x, m_gameroomBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 11, ColorCode::black})->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                backgroundColor(ColorCode::white)->
                id(seg::toUType(resource::WAITINGROOM_GAMEROOMBOX))->
                width(m_gameroomBoxWidth)->
                height(m_gameroomBoxHeight)->
                borderColor(ColorCode::cyan)->
                borderThick(3)->
                enabled(true);

        addControl(bld.build());
    }
    {
        ListBoxBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 11, ColorCode::black})->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                backgroundColor(ColorCode::white)->
                id(seg::toUType(resource::WAITINGROOM_CHATBOX))->
                width(m_chatBoxWidth)->
                height(m_chatBoxHeight)->
                borderColor(ColorCode::dimgray)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }
    {
        EditLabelBuilder bld(getWindow(), {m_chatBoxBeginPoint.x, m_chatBoxBeginPoint.y + m_chatBoxHeight + 5}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 13, ColorCode::black})->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                backgroundColor(ColorCode::white)->
                id(seg::toUType(resource::WAITINGROOM_CHAREDIT))->
                width(m_chatBoxWidth)->
                height(30)->
                borderColor(ColorCode::dimgray)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }
    {
        ListBoxBuilder bld(getWindow(), {m_userBoxBeginPoint.x, m_userBoxBeginPoint.y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 11, ColorCode::black})->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                backgroundColor(ColorCode::white)->
                id(seg::toUType(resource::WAITINGROOM_USERBOX))->
                width(m_userBoxWidth)->
                height(m_userBoxHeight)->
                borderColor(ColorCode::dimgray)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y}, "CREATE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                backgroundColor(ColorCode::dimgray)->
                id(seg::toUType(resource::WAITINGROOM_CREATE))->
                width(m_btnWidth)->
                height(m_btnHeight)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {m_createBtnBeginPoint.x, m_createBtnBeginPoint.y + m_btnHeight + 10}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
                backgroundColor(ColorCode::dimgray)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                id(seg::toUType(resource::WAITINGROOM_DISCONNECT))->
                width(m_btnWidth)->
                height(m_btnHeight)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }

    m_waitingRoom.initialize();

    TDisplayInterface::onInitialize();
}

void TWaitingRoomDisplay::onDraw()
{
    TDisplayInterface::onDraw();
}

void TWaitingRoomDisplay::updateObserver(const Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::WAITINGROOMS_RESPONSE_INIT_INFO:
            recvWaitingRoomInitInfo(packet);
            break;
        case messageInfo::WAITINGROOMS_RECV_CHAT:
            recvChat(packet);
            break;
        case messageInfo::WAITINGROOMS_RESPONSE_CREATE:
            createGameroom(packet);
            break;
    }
    refresh();
}

void TWaitingRoomDisplay::recvWaitingRoomInitInfo(const Packet& packet)
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
    for (int i = 0; i < roomCount; ++i) {
        const Json::Value jsonroom = roomRoot[i];

        TGameRoom gameroom;
        gameroom.fromJson(jsonroom);

        const auto ctl = getControl<ListBox>(tetris::resource::WAITINGROOM_GAMEROOMBOX);

        RoomInfo roominfo{gameroom.getRoomNumber(), gameroom.getRoomName(), gameroom.getMaketime(),
                          gameroom.getUnique(), gameroom.getPlayerContainer().size(), gameroom.getFullCount()};
        ctl->appendItem(make_shared<RoomInfo>(roominfo));

    }

    const auto ctl = getControl<ListBox>(tetris::resource::WAITINGROOM_USERBOX);
    auto dummyPlayer = make_shared<TPlayer>();

    const size_t plyCount = root["player_count"].asUInt();
    const Json::Value playerRoot = root[game_interface::NAME_PLAYER.data()];
    for (int i = 0; i < plyCount; ++i) {
        const Json::Value jsonPlayer = playerRoot[i];

        dummyPlayer->fromJson(jsonPlayer);
        ctl->appendItem(make_shared<UserInfo>(dummyPlayer->getUserName(), dummyPlayer->getMaketime(),
                                              dummyPlayer->getUnique()));
    }
}

void TWaitingRoomDisplay::onClickExit(const void* click)
{
    TPlayer::getInstance()->disconnectServer();
    TDisplayInterface::onClose();
}

void TWaitingRoomDisplay::onClickCreateGameRoom(const void* click)
{

    auto createGameroomDisplay = seg::make_display<TCreateGameroomDisplay>();
    createGameroomDisplay->setWindowHeight(250);
    createGameroomDisplay->setWindowWidth(350);
    createGameroomDisplay->setWindowTitle("Create Room");

    /*if (createGameroomDisplay->modal() == seg::resource::BTN_OK) {
        if (!PacketQueue::getInstance().exist(TGameRoom::getInstance()->getUnique())) {
            PacketQueue::getInstance().attach(TGameRoom::getInstance());
        }

        const string& roomname = createGameroomDisplay->getRoomName();

        Json::Value root;
        root["name"] = roomname;

        Packet packet{{m_waitingRoom.getUnique(), TPlayer::getInstance()->getUnique(),
                       messageInfo::WAITINGROOMS_REQUEST_CREATE}, root};
        TPlayer::getInstance()->sendPacket(packet);

    }*/
}

void TWaitingRoomDisplay::sendChat(const void* event)
{
    auto keyevent = static_cast<const SDL_KeyboardEvent*>(event);
    if (keyevent->keysym.sym == SDLK_RETURN) {
        const auto ctl = getControl<EditLabel>(tetris::resource::WAITINGROOM_CHAREDIT);
        ChatInfo chatinfo{TPlayer::getInstance()->getUserName(), ctl->getLabelString(), std::time(0)};

        Packet packet{
                {m_waitingRoom.getUnique(), TPlayer::getInstance()->getUnique(), messageInfo::WAITINGROOMS_SEND_CHAT},
                chatinfo.toJson()};
        TPlayer::getInstance()->sendPacket(packet);

        ctl->clearString();
    }
}

void TWaitingRoomDisplay::recvChat(const Packet& packet)
{
    const string chat = packet.getPayload()["chat"].asString();
    const auto ctl = getControl<ListBox>(tetris::resource::WAITINGROOM_CHATBOX);

    ChatInfo chatinfo;
    auto json = packet.getPayload();
    chatinfo.fromJson(json);

    ctl->appendItem(make_shared<ChatInfo>(chatinfo));
}

void TWaitingRoomDisplay::createGameroom(const Packet& packet)
{

    auto gameroomDisplay = seg::make_display<TMultiGameRoomDisplay>();
    gameroomDisplay->getGameRoom()->fromJson(packet.getPayload());
    gameroomDisplay->setWindowTitle("Tetris Game");
    gameroomDisplay->modaless();

}
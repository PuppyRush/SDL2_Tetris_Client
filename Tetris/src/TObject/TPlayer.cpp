//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayer.h"
#include "Tetris/include/TFigureBuilder.h"

#include "GameInterface/include/PacketQueue.h"
//#include "GameInterface/include/JsonHelper.h"

SDL_TETRIS

using namespace std;
using namespace tetris_module;
using namespace game_interface;
using namespace game_interface::packet;
using namespace seg;

TPlayer::TPlayer()
{
    //after set id recvied GameInterface_Init data from server
    setUnique(NULL_ID);

    auto reactor = make_shared<ACE_Reactor>(new ACE_Select_Reactor{});
    m_service = make_shared<ClientService>(reactor);
}

TPlayer::~TPlayer()
{
    endGame();
}

void TPlayer::initialize()
{
    auto board = getController().getBoard();

    SEG_Point gameboardBeginPoint{50, 50}, gameboardPoint{0, 0};
    seg::t_size blockLen{0};

    switch (m_order) {
        case 0: {

            gameboardBeginPoint = {GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y};
            blockLen = FIGURE_UNIT_LEN;

            auto nextboard = getController().getNextFigureBoard();
            nextboard->setStartDisplayPoint(SEG_Point{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                                   GAMEBOARD_BEGIN_Y});
            nextboard->setblockLength(FIGURE_UNIT_LEN);
            break;
        }
        case 1:
        case 2:
        case 3:
            gameboardBeginPoint = {OTHER_GAMEBOARD_BEGIN_X, OTHER_GAMEBOARD_BEGIN_Y};
            gameboardBeginPoint.x += (m_order - 1) * GAMEBOARD_GAP;
            blockLen = OTHER_UNIT_LENGTH;
            break;

        case 4:
        case 5:
        case 6:
            gameboardBeginPoint = {OTHER_GAMEBOARD_BEGIN_X, OTHER_GAMEBOARD_BEGIN_Y};
            gameboardBeginPoint.x += (m_order - 4) * GAMEBOARD_GAP;
            gameboardBeginPoint.y += OTHER_GAMEBOARD_DISPLAY_HEIGHT + GAMEBOARD_GAP;
            blockLen = OTHER_UNIT_LENGTH;
            break;
    }

    board->setStartDisplayPoint(gameboardBeginPoint);
    board->setblockLength(blockLen);
}

void TPlayer::startGame()
{

}

void TPlayer::command(const t_eventType event)
{
    m_gameCtl.command(event);

    Json::Value json;
    json["command"] = event;

    Packet packet{{getUnique(), getUnique(), messageInfo::GAME_REQUEST_BOARDINFO}, json};
    this->sendPacket(packet);
}

void TPlayer::endGame()
{

}

bool TPlayer::connectServer()
{
    assert(!getUserName().empty());
    auto result = m_service->connectServer();

    //first call faster than server.
    sendDummySignal();

    return result;
}

void TPlayer::disconnectServer()
{
    Header header{this->getUnique(), this->getUnique(), messageInfo::DISCONNECT};
    Packet p{header};
    sendPacket(p);
}

void TPlayer::sendPacket(const Packet& packet) const
{
    m_service->sendPacket(packet);
}

void TPlayer::updateObserver(const Packet& packet)
{
    /*if(packet.getHeader().message == messageInfo::PLAYER_INIT_INFO)
        this->setUnique(packet.getHeader().destId);*/

    switch (packet.getHeader().message) {
        case messageInfo::PLAYER_INIT_INFO:
            recvInfo(packet);
            requestWaitingRoomInitInfo();
            break;

    }
}

void TPlayer::sendBoardInfo(const t_id gameRoomUnique)
{
    /*auto fig = this->m_gameCtl.getCurrentFigure();

    time_t rawtime;
    time (&rawtime);

    auto plyJson = this->toJson();
    plyJson[fig->getUniqueName().data()] = fig->toJson();

    Packet packet{{gameRoomUnique, getUnique(), messageInfo::GAME_REQUEST_BOARDINFO}, plyJson};
    this->sendPacket(packet);*/
}

void TPlayer::recvBoardInfo(const Packet& packet)
{
    auto json = packet.getPayload();
    command(json["command"].asInt());


    /*auto plyJson = packet.getPayload();

    TFigureBuilder dummyBld({0,0});
    auto dummyFigure = dummyBld.build();
    dummyFigure->fromJson(plyJson[dummyFigure->getUniqueName().data()]);

    TFigureBuilder bld{dummyFigure->getPoint()};
    bld.figure(dummyFigure->getClass());
    bld.unitType(UnitType::Moving);
    auto figure = bld.build();

    m_gameCtl.forceSet(figure.get());*/
}

void TPlayer::recvInfo(const Packet& packet)
{
    setUnique(packet.getHeader().senderId);

    const Json::Value json = packet.getPayload();
    setUnique(json["unique"].asInt());

    auto playerJosn = toJson();

    Header header{this->getUnique(), this->getUnique(), messageInfo::PLAYER_INIT_INFO};
    Packet p{header, playerJosn};
    sendPacket(p);
}

void TPlayer::sendDummySignal()
{
    Header header{this->getUnique(), this->getUnique(), messageInfo::DUMMY_SIGNAL};
    Packet p{header};
    sendPacket(p);
}

void TPlayer::requestWaitingRoomInitInfo()
{
    Header header{this->getUnique(), this->getUnique(), messageInfo::WAITINGROOMS_REQUEST_INIT_INFO};
    Packet p{header};
    sendPacket(p);
}

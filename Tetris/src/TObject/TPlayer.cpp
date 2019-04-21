//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayer.h"
#include "../TFiguers/TFigureBuilder.h"

#include "GameInterface/src/Online/PacketQueue.h"
#include "GameInterface/src/Online/JsonHelper.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;
using namespace sdleasygui;

TPlayer::TPlayer()
{
    //after set id recvied init data from server
    setUnique(NULL_ID);
}

TPlayer::~TPlayer()
{
    endGame();
}

void TPlayer::startGame(){
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

const bool TPlayer::connectServer()
{
    assert(!getUserName().empty());
    auto result = m_clientCtl.connectServer();

    //first call faster than server.
    sendDummySignal();

    return result;
}

void TPlayer::sendPacket(Packet &packet)
{
    m_clientCtl.send(packet);
}

void TPlayer::updateObserver(const Packet& packet)
{
    /*if(packet.getHeader().message == messageInfo::PLAYER_INIT_INFO)
        this->setUnique(packet.getHeader().destId);*/

    switch(packet.getHeader().message)
    {
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


void TPlayer::recvBoardInfo(const game_interface::Packet& packet)
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

void TPlayer::recvInfo(const game_interface::Packet& packet)
{
    setUnique(packet.getHeader().senderId);

    const Json::Value json = packet.getPayload();
    setUnique(json["unique"].asInt());

    auto playerJosn = toJson();

    Packet::Header header{this->getUnique(), this->getUnique(), messageInfo::PLAYER_INIT_INFO};
    Packet p{header, playerJosn};
    sendPacket(p);
}

void TPlayer::sendDummySignal()
{
    Packet::Header header{this->getUnique(), this->getUnique(), messageInfo::DUMMY_SIGNAL};
    Packet p{header};
    sendPacket(p);
}

void TPlayer::requestWaitingRoomInitInfo()
{
    Packet::Header header{this->getUnique(), this->getUnique(), messageInfo::WAITINGROOMS_REQUEST_INIT_INFO};
    Packet p{header};
    sendPacket(p);
}

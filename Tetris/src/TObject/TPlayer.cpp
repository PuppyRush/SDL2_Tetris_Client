//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayer.h"
#include "../TFiguers/TFigureBuilder.h"
#include "GameInterface/src/Online/JsonHelper.h"
#include "GameInterface/src/Online/PacketQueue.h"

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

    auto fig = this->m_gameCtl.getCurrentFigure();

    time_t rawtime;
    time (&rawtime);

    string timeStr = to_string(rawtime);
    auto gameboardBitset = JsonHelper::toGameboardBitset(
        toUType( fig->getClass()),
        toUType( fig->getType()),
        fig->getPoint().x,
        fig->getPoint().y);

    auto jsonObj = JsonHelper::toJson("test", m_ip.str(), timeStr, gameboardBitset.to_string());

    Packet packet{{getUnique(), getUnique(), messageInfo::GAME_TETRISBOARD_INFO}, jsonObj};
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

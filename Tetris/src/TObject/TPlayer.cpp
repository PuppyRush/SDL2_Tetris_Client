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
    m_gameCtl = make_shared<TFigureController>();
}

void TPlayer::command(const t_eventType event)
{
    m_gameCtl->command(event);

    auto fig = this->m_gameCtl->getCurrentFigure();

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
    if(m_gameCtl && m_gameCtl.get())
    {
        m_gameCtl.reset();
        m_gameCtl = nullptr;
    }
    else if(m_gameCtl)
        m_gameCtl = nullptr;

}

void TPlayer::connectServer()
{
    assert(!getUserName().empty());
    m_clientCtl.connectServer();

    //first call faster than server.

    sendDummySignal();
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
            break;
        case messageInfo::WAITINGROOMS_INIT:
            recvWaitingRoomInit(packet);
            break;

    }
}

void TPlayer::recvWaitingRoomInit(const game_interface::Packet& packet)
{
    const Json::Value json = packet.getPayload();
    if(json["wroom_count"].asUInt()==1)
    {
        Json::Value wroom = json["wroom0"];
        string roomname =  wroom["roomname"].asString();
        t_id roomnumber =  wroom["roomnumber"].asUInt();
    }
    else
    {
        //wroom 두개일땐 다시 구현.
        assert(0);
    }
}


void TPlayer::recvInfo(const game_interface::Packet& packet)
{
    setUnique(packet.getHeader().senderId);

    const Json::Value json = packet.getPayload();
    setUnique(json["unique"].asInt());

    sendInitInfo();
}

void TPlayer::sendDummySignal()
{
    Packet::Header header{this->getUnique(), this->getUnique(), messageInfo::DUMMY_SIGNAL};
    Packet p{header};
    sendPacket(p);
}

void TPlayer::sendInitInfo()
{
    Json::Value json;
    json["id"] = this->getUserName();
    json["ip"] = this->m_ip.ip;

    Packet::Header header{this->getUnique(), this->getUnique(), messageInfo::PLAYER_INIT_INFO};
    Packet p{header, json};
    sendPacket(p);
}

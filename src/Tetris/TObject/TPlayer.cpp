//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayer.h"
#include "../TFiguers/TFigureBuilder.h"
#include "GameInterface/Online/JsonHelper.h"
#include "GameInterface/Online/PacketQueue.h"

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
    //Json::StyledWriter styledWriter;
    //auto bufstr = styledWriter.write(jsonObj);

    Packet packet{{getUnique(), messageDirection::CLIENT, messageInfo::GAME_TETRISBOARD_INFO}, jsonObj};
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
}

void TPlayer::sendPacket(Packet &packet)
{
    m_clientCtl.send(packet);
}

void TPlayer::updateObserver(const Observer&, const Packet packet)
{
    switch(packet.getHeader().message)
    {
        case messageInfo::PLAYER_INIT_INFO:
            recvInfo(packet);
            break;
    }
}

void TPlayer::recvInfo(const game_interface::Packet& packet)
{
    const Json::Value json = packet.getPayload();
    setUnique(json.asInt());

    requestInfo();
}

void TPlayer::requestInfo()
{
    Json::Value json;
    json["id"] = this->getUserName();

    Packet::Header header{this->getUnique(),messageDirection::CLIENT, messageInfo::PLAYER_INIT_INFO};
    Packet p{header, json};
    sendPacket(p);

}

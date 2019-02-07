//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayer.h"
#include "../TFiguers/TFigureBuilder.h"
#include "../TClient/JsonHelper.h"
SDL_TETRIS


TPlayer::TPlayer()
{}

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
    send(TClientController::packet_type("",3));
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
    m_clientCtl.connectServer();
}

void TPlayer::send(TClientController::packet_type packet)
{

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
    Json::StyledWriter styledWriter;
    auto bufstr = styledWriter.write(jsonObj);

    m_clientCtl.send(make_pair(bufstr.c_str(), bufstr.size()));
}

TClientController::packet_type TPlayer::recv()
{
    TClientController::packet_type packet = m_clientCtl.recv();






}
//
// Created by chaed on 19. 1. 13.
//

#include "TPlayer.h"

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
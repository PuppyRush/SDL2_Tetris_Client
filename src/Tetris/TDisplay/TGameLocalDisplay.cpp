//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "Tetris/Common/Resource.h"
#include "../Common/Event.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "TGameLocalDisplay.h"

SDL_TETRIS



TGameLocalDisplay::TGameLocalDisplay()
{
    m_display = TDisplay::Game;
    m_mode = TLocalMode::Local;
}


void TGameLocalDisplay::onClickedStart()
{
    auto ply = std::make_shared<TPlayer>();
    ply->startGame();
    m_players.emplace_back(ply);

    auto board = ply->getController()->getBoard();

    m_drawLine = TOptionManager::getInstance()->isDrawLine();

    board->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
    board->setblockLength(FIGURE_UNIT_LEN);

    auto nextboard = ply->getController()->getNextFigureBoard();
    nextboard->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN, GAMEBOARD_BEGIN_Y});
    nextboard->setblockLength(FIGURE_UNIT_LEN);

    m_figureTimer = SDL_AddTimer(1000, my_callbackfunc, nullptr);
    m_gamestart = true;

    auto ctl = getControll(resource::GAME_START);
    ctl->setEnabled(false);
}

void TGameLocalDisplay::onClickedSuspend()
{

}

void TGameLocalDisplay::registerEvent() {

    event_buttonClick(resource::GAME_START, std::bind(&TGameLocalDisplay::onClickedStart, this));
}

void TGameLocalDisplay::onPreInitialize()
{


    t_size begin_y = WINDOW_HEIGHT/10*3;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_START))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_SUSPEND))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_END))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }

    DisplayInterface::onPreInitialize();
}

void TGameLocalDisplay::onClose()
{

    TGameDisplay::onClose();
}

void TGameLocalDisplay::onCreate()
{

    TGameDisplay::onCreate();
}


void TGameLocalDisplay::event(const SDL_Event *event) {

    TGameDisplay::event(event);
}

void TGameLocalDisplay::timer()
{

}

void TGameLocalDisplay::onDraw() {
    TGameDisplay::onDraw();
}
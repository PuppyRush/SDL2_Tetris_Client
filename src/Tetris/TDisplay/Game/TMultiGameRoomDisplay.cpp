//
// Created by chaed on 19. 2. 6.
//

#include <jsoncpp/json/json.h>

#include "TMultiGameRoomDisplay.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "GameInterface/Event.h"
#include "GameInterface/Online/JsonHelper.h"
#include "Tetris/Common/TResource.h"
#include "Tetris/TFiguers/TFigureBuilder.h"
#include "../../TOption/TOptionManager.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;
using namespace std;

TMultiGameRoomDisplay::TMultiGameRoomDisplay()
{
    m_display = toUType( TDisplay::Game);
    m_mode = TLocalMode::Online;
}

void TMultiGameRoomDisplay::onClickedStart()
{
    {
        auto ply = std::make_shared<TPlayer>();
        ply->startGame();
        m_players.emplace_back(ply);

        ply->connectServer();
        auto board = ply->getController()->getBoard();

        board->setStartDisplayPoint(Point{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = ply->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(Point{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                               GAMEBOARD_BEGIN_Y});
        nextboard->setblockLength(FIGURE_UNIT_LEN);
    }

    //
    {
        auto echoPly = std::make_shared<TPlayer>();
        echoPly->startGame();
        m_players.emplace_back(echoPly);

        auto board = echoPly->getController()->getBoard();

        const auto beginX = GAMEBOARD_BEGIN_X+600;
        board->setStartDisplayPoint(Point{beginX, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = echoPly->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(Point{beginX + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                               GAMEBOARD_BEGIN_Y});
        nextboard->setblockLength(FIGURE_UNIT_LEN);
    }

    TimerAdder tAdder(1000,toUType(TetrisEvent::TETRIS_EVENT_FIGURETIMER));
    tAdder.windowsId(this->getWindowID());
    m_figureTimer = tAdder.addTimer();

    m_drawLine = TOptionManager::getInstance()->isDrawLine();
    m_gamestart = true;

    auto ctl = getControll(resource::GAME_START);
    ctl->setEnabled(false);
}

void TMultiGameRoomDisplay::onClickedSuspend()
{}

void TMultiGameRoomDisplay::onDraw()
{
    TGameDisplay::onDraw();
}

void TMultiGameRoomDisplay::onPreInitialize()
{


    t_size begin_y = WINDOW_HEIGHT/10*3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_START))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_SUSPEND))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_END))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onPreInitialize();
}

void TMultiGameRoomDisplay::onClose()
{
    DisplayInterface::onClose();
}

void TMultiGameRoomDisplay::onCreate()
{
    DisplayInterface::onCreate();
}

void TMultiGameRoomDisplay::registerEvent()
{
    event_buttonClick(toUType(resource::GAME_START), std::bind(&TMultiGameRoomDisplay::onClickedStart, this));
}

void TMultiGameRoomDisplay::onUserEvent(const SDL_UserEvent* event)
{
    switch (event->type) {
        case RECV_DATA:
            if(m_players.size()==2) {

                Json::Value json;
                string strbuf((char *)event->data1);

                Json::Reader reader;
                reader.parse(strbuf, json);

                t_coord x{0}, y{0};
                int tclass;
                int  type;

                string id;
                string ip;
                string time;
                string board;
                JsonHelper::jsonRef(json,id,ip,time,board);
                JsonHelper::ref(board, tclass, type, x,y);

                TFigureBuilder bld({x,y});
                bld.figure(TFigureClass(tclass));
                bld.type(TFigureType(type));

                auto figure = bld.build();
                m_players.at(1)->getController()->forceSet(figure.get());
                refresh();
            }
            break;
        default:;
    }

    TGameDisplay::onUserEvent(event);
}


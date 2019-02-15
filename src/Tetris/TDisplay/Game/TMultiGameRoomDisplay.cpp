//
// Created by chaed on 19. 2. 6.
//

#include <jsoncpp/json/json.h>

#include "TMultiGameRoomDisplay.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "GameInterface/Event.h"
#include "Tetris/TClient/JsonHelper.h"
#include "Tetris/Common/TResource.h"
#include "Tetris/TFiguers/TFigureBuilder.h"

SDL_TETRIS

Uint32 callback(Uint32 interval, void *param) {

    SDL_UserEvent userevent;
    userevent.type = TETRIS_EVENT_FIGURETIMER;
    userevent.code = 0;
    userevent.windowID =  static_cast<TMultiGameRoomDisplay*>(param)->getWindowID();

    SDL_Event event;
    event.type = TETRIS_EVENT_FIGURETIMER;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

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

        board->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = ply->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
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
        board->setStartDisplayPoint(TPoint{beginX, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = echoPly->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(TPoint{beginX + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                               GAMEBOARD_BEGIN_Y});
        nextboard->setblockLength(FIGURE_UNIT_LEN);
    }

    m_drawLine = TOptionManager::getInstance()->isDrawLine();
    m_figureTimer = SDL_AddTimer(1000, callback, this);
    m_gamestart = true;

    auto ctl = getControll(toUType(resource::GAME_START));
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
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_START))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_SUSPEND))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_END))->
            background_color(TColorCode::white)->
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
                pushDrawDisplayEvent();
            }
            break;
        default:;
    }

    TGameDisplay::onUserEvent(event);
}


//
// Created by chaed on 19. 2. 6.
//

//#include <jsoncpp/json/json.h>

#include "TMultiGameRoomDisplay.h"
#include "SDL2EasyGUI/include/Button.h"
#include "GameInterface/include/Event.h"
#include "TResource.h"
#include "Tetris/include/TFigureBuilder.h"
#include "../../TOption/TOptionManager.h"

SDL_TETRIS
using namespace std;
using namespace game_interface;
using namespace game_interface::packet;
using namespace seg;
using namespace tetris_module;

TMultiGameRoomDisplay::TMultiGameRoomDisplay(const seg::t_id displayId)
        : TGameDisplay(displayId)
{
    m_display = game_interface::toUType(TDisplay::Game);
    m_mode = TLocalMode::Online;


}

void TMultiGameRoomDisplay::onClickedStart(const void* click)
{
    TGameDisplay::onClickedStart(click);
}

void TMultiGameRoomDisplay::onClickedSuspend(const void* click)
{}

void TMultiGameRoomDisplay::onDraw()
{
    TGameDisplay::onDraw();
}

void TMultiGameRoomDisplay::onInitialize()
{
    t_size begin_y = WINDOW_HEIGHT - 300;
    t_size begin_x = WINDOW_WIDTH - 200;
    {
        ButtonBuilder bld(getWindow(), {begin_x, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::GAME_START))->
                backgroundColor(ColorCode::white)->
                width(150)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {begin_x, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::GAME_SUSPEND))->
                backgroundColor(ColorCode::white)->
                width(150)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {begin_x, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::GAME_END))->
                backgroundColor(ColorCode::white)->
                width(150)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }

    TGameDisplay::onInitialize();
}

void TMultiGameRoomDisplay::onClose()
{
    TGameDisplay::onClose();
}

void TMultiGameRoomDisplay::onCreate()
{
    TGameDisplay::onCreate();
}

void TMultiGameRoomDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(game_interface::toUType(resource::GAME_START),
                     &TMultiGameRoomDisplay::onClickedStart,
                     this);
}

void TMultiGameRoomDisplay::updateObserver(const Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::GAME_RESPONSE_BOARDINFO:
            if (m_players.size() == 2) {
                m_players.back()->recvBoardInfo(packet);
            }
            break;
        default:;
    }

    TGameDisplay::updateObserver(packet);
}

void TMultiGameRoomDisplay::onTimerEvent(const SDL_UserEvent* user)
{

    switch (user->code) {
        case TETRIS_EVENT_FIGURETIMER:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            if (!m_players.empty()) {

                m_players.front()->sendBoardInfo(m_gameroom->getUnique());
            }

            break;
        default:;
    }

    TGameDisplay::onTimerEvent(user);
}

void TMultiGameRoomDisplay::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    switch (key->type) {
        case SDL_KEYDOWN:
            if (!m_players.empty()) {
                auto& me = m_players.front();
                me->sendBoardInfo(m_gameroom->getUnique());
                refresh();
            }
            break;
        default:;
    }

    TGameDisplay::onKeyboardEvent(key);
}

void TMultiGameRoomDisplay::onUserEvent(const SDL_UserEvent* event)
{

    TGameDisplay::onUserEvent(event);
}


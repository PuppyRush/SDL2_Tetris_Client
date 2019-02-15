//
// Created by chaed on 18. 12. 18.
//

#include "TMainOnlineDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "Tetris/Common/TResource.h"
#include "Tetris/TDisplay/Game/TMultiGameRoomDisplay.h"

SDL_TETRIS

TMainOnlineDisplay::TMainOnlineDisplay()
{
    m_mode = TLocalMode::Online;
}

void TMainOnlineDisplay::registerEvent()
{
    event_buttonClick(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON), std::bind(&TMainOnlineDisplay::onClickedEnterServer, this));
    event_buttonClick(toUType(resource::MAIN_OPTION_BUTTON), std::bind(&TMainOnlineDisplay::onClickedOption, this));
}

void TMainOnlineDisplay::onPreInitialize() {

    t_size begin_y = WINDOW_HEIGHT/3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            id(toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
            width(240)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/2-50, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_OPTION_BUTTON))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(),{WINDOW_WIDTH/2-50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_EXIT))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }

    ::DisplayInterface::onPreInitialize();
}

void TMainOnlineDisplay::onTimer()
{

}

void TMainOnlineDisplay::onDraw()
{
    TMainDisplay::onDraw();
}

void TMainOnlineDisplay::onClickedOption()
{
    auto dlg = make_shared<TOptionDisplay>();
    dlg->modal();
}

void TMainOnlineDisplay::onClickedEnterServer()
{
    auto dlg = make_shared<TMultiGameRoomDisplay>();
    dlg->modal();
}
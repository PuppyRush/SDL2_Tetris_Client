//
// Created by chaed on 18. 12. 18.
//


#include "TMainLocalDisplay.h"
#include "Tetris/TDisplay/Game/TSingleGameDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "Tetris/Common/TResource.h"

SDL_TETRIS

TMainLocalDisplay::TMainLocalDisplay()
{
    m_mode = TLocalMode::Local;
}

void TMainLocalDisplay::registerEvent() {

    event_buttonClick(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON), std::bind(&TMainLocalDisplay::onClickedStartLocalGame, this));
    event_buttonClick(toUType(resource::MAIN_OPTION_BUTTON), std::bind(&TMainLocalDisplay::onClickedOption, this));
}

void TMainLocalDisplay::onPreInitialize() {
    //setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/3;

    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 100, begin_y}, "PLAY ALONE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            id(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON))->
            width(200)->
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

void TMainLocalDisplay::onClickedStartLocalGame()
{
    auto dlg = make_shared<TSingleGameDisplay>();
    dlg->modal();
}

void TMainLocalDisplay::onClickedOption()
{
    auto dlg = make_shared<TOptionDisplay>();
    dlg->modal();
}

void TMainLocalDisplay::onTimer()
{

}

void TMainLocalDisplay::onDraw()
{
    DisplayInterface::onDraw();
}

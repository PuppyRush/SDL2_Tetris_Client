//
// Created by chaed on 18. 12. 18.
//


#include "TLocalMainDisplay.h"
#include "Tetris/TDisplay/Game/TSingleGameDisplay.h"
#include "Tetris/TDisplay/TOptionDisplay.h"
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "Tetris/Common/TResource.h"

SDL_TETRIS
using namespace std;
using namespace game_interface;
using namespace sdleasygui;

TLocalMainDisplay::TLocalMainDisplay()
{
    m_mode = TLocalMode::Local;
}

void TLocalMainDisplay::registerEvent() {

    event_buttonClick(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON), std::bind(&TLocalMainDisplay::onClickedStartLocalGame, this));
    event_buttonClick(toUType(resource::MAIN_OPTION_BUTTON), std::bind(&TLocalMainDisplay::onClickedOption, this));
}

void TLocalMainDisplay::onInitialize() {
    //setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/3;

    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 100, begin_y}, "PLAY ALONE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON))->
            width(200)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/2-50, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::MAIN_OPTION_BUTTON))->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(),{WINDOW_WIDTH/2-50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::MAIN_EXIT))->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    ::DisplayInterface::onInitialize();
}

void TLocalMainDisplay::onClickedStartLocalGame()
{
    auto dlg = make_shared<TSingleGameDisplay>();
    dlg->setWindowHeight(WINDOW_HEIGHT);
    dlg->setWindowWidth(WINDOW_WIDTH);
    dlg->modal();
}

void TLocalMainDisplay::onClickedOption()
{
    auto dlg = make_shared<TOptionDisplay>();
    dlg->setWindowHeight(WINDOW_HEIGHT);
    dlg->setWindowWidth(WINDOW_WIDTH);
    dlg->modal();
}

void TLocalMainDisplay::onTimerEvent()
{

}

void TLocalMainDisplay::onDraw()
{
    DisplayInterface::onDraw();
}

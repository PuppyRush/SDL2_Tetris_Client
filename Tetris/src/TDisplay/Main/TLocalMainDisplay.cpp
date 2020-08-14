//
// Created by chaed on 18. 12. 18.
//


#include "TLocalMainDisplay.h"
#include "../Game/TSingleGameDisplay.h"
#include "../TOptionDisplay.h"
#include "SDL2EasyGUI/include/DisplayController.h"
#include "SDL2EasyGUI/include/Button.h"
#include "TResource.h"

SDL_TETRIS
using namespace std;
using namespace game_interface;
using namespace seg;

TLocalMainDisplay::TLocalMainDisplay()
{
    m_mode = TLocalMode::Local;
}

void TLocalMainDisplay::registerEvent()
{

    SEG_LBUTTONCLICK(game_interface::toUType(resource::MAIN_SINGLE_GAME_START_BUTTON),
                     &TLocalMainDisplay::onClickedStartLocalGame, this);
    SEG_LBUTTONCLICK(game_interface::toUType(resource::MAIN_OPTION_BUTTON), &TLocalMainDisplay::onClickedOption, this);
}

void TLocalMainDisplay::onInitialize()
{
    //setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT / 3;

    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 100, begin_y}, "PLAY ALONE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                backgroundColor(ColorCode::white)->
                id(game_interface::toUType(resource::MAIN_SINGLE_GAME_START_BUTTON))->
                width(200)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 50, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_OPTION_BUTTON))->
                backgroundColor(ColorCode::white)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_EXIT))->
                backgroundColor(ColorCode::white)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    TMainDisplay::onInitialize();
}

void TLocalMainDisplay::onClickedStartLocalGame(const void* click)
{
    auto dlg = seg::make_display<TSingleGameDisplay>();
    dlg->setWindowHeight(WINDOW_HEIGHT);
    dlg->setWindowWidth(WINDOW_WIDTH);
    dlg->modal();
}

void TLocalMainDisplay::onClickedOption(const void* click)
{
    auto dlg = seg::make_display<TOptionDisplay>();
    dlg->setWindowHeight(WINDOW_HEIGHT);
    dlg->setWindowWidth(WINDOW_WIDTH);
    dlg->modal();
}

void TLocalMainDisplay::onDraw()
{
    TMainDisplay::onDraw();
}

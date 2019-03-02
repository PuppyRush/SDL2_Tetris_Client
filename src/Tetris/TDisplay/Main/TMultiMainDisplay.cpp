//
// Created by chaed on 18. 12. 18.
//

#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/Windows/DisplayController.h"

#include "TMultiMainDisplay.h"
#include "TEnterServerDisplay.h"
#include "../TOptionDisplay.h"
#include "../../Common/TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

TMultiMainDisplay::TMultiMainDisplay()
{
    m_mode = TLocalMode::Online;
}

void TMultiMainDisplay::registerEvent()
{
    event_buttonClick(toUType(resource::MAIN_MULTI_GAME_START_BUTTON), std::bind(&TMultiMainDisplay::onClickedEnterServer, this));
    event_buttonClick(toUType(resource::MAIN_OPTION_BUTTON), std::bind(&TMultiMainDisplay::onClickedOption, this));
}

void TMultiMainDisplay::onPreInitialize() {

    t_size begin_y = WINDOW_HEIGHT/3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
            width(240)->
            height(50)->
            borderColor(ColorCode::silver)->
            borderThick(4)->
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

    DisplayInterface::onPreInitialize();
}

void TMultiMainDisplay::onTimerEvent()
{

}

void TMultiMainDisplay::onDraw()
{
    TMainDisplay::onDraw();
}

void TMultiMainDisplay::onClickedOption()
{
    auto dlg = std::make_shared<TOptionDisplay>();
    dlg->modal();
}

void TMultiMainDisplay::onClickedEnterServer()
{
    auto dlg = std::make_shared<TEnterServerDisplay>();
    dlg->modal();
}
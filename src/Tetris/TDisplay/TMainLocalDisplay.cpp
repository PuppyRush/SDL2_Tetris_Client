//
// Created by chaed on 18. 12. 18.
//


#include "TMainLocalDisplay.h"
#include "TGameLocalDisplay.h"
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "Tetris/Common/Resource.h"

SDL_TETRIS

TMainLocalDisplay::TMainLocalDisplay()
{
    m_mode = TLocalMode::Local;
}

void TMainLocalDisplay::registerEvent() {

    event_buttonClick(resource::MAIN_SINGLE_GAME_START_BUTTON, std::bind(&TMainLocalDisplay::onClickedStartLocalGame, this));
    event_buttonClick(resource::MAIN_MULTI_GAME_START_BUTTON, std::bind(&TMainLocalDisplay::onClickedEnterServer, this));

}

void TMainLocalDisplay::onPreInitialize() {
    //setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/3;

    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 100, begin_y}, "PLAY ALONE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            id(toUType(resource::MAIN_SINGLE_GAME_START_BUTTON))->
            width(200)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/2-50, begin_y}, "OPTION");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_OPTION_BUTTON))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(),{WINDOW_WIDTH/2-50, begin_y}, "EXIT");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_EXIT))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    ::DisplayInterface::onPreInitialize();
}




void TMainLocalDisplay::onClickedStartLocalGame()
{
    DisplayController::getInstance()->modal(make_shared<TGameLocalDisplay>());
}

void TMainLocalDisplay::timer()
{

}

void TMainLocalDisplay::event(const SDL_Event *event) {

    DisplayInterface::event(event);
}

void TMainLocalDisplay::onDraw()
{

}

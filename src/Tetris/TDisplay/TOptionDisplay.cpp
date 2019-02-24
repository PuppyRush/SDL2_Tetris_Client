//
// Created by chaed on 18. 12. 18.
//

#include "TOptionDisplay.h"
#include "../Common/TResource.h"
#include "SDLEasyGUI/Controller/StaticLabel.h"
#include "SDLEasyGUI/Controller/Button.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

TOptionDisplay::TOptionDisplay()
{
    m_display = toUType(TDisplay::Option);
    m_mode = TLocalMode::All;
};

void TOptionDisplay::registerEvent() {
    event_buttonClick(toUType(resource::OPTION_BACK), std::bind(&TOptionDisplay::onClickedBack, this));
}

void TOptionDisplay::onPreInitialize() {
    setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT / 4;
    t_size begin_x = WINDOW_WIDTH / 3;

    {
        StaticLabelBuilder bld(getWindow(), {begin_x - 100, begin_y}, "SPEED");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(false);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 60, begin_y}, "1");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 120, begin_y}, "2");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 180, begin_y}, "3");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 240, begin_y}, "4");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 60, begin_y + 60}, "5");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 120, begin_y + 60}, "6");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 180, begin_y + 60}, "7");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 240, begin_y + 60}, "8");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addControll(bld.build());
    }

    begin_y = WINDOW_HEIGHT / 4 + 200;

    {
        StaticLabelBuilder bld(getWindow(),{begin_x - 100, begin_y}, "MAP");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(80)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addControll(bld.build());
    }

    {
        ButtonBuilder bld(getWindow(),{begin_x + 60, begin_y}, "Pyramid");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(120)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addControll(bld.build());
    }

    {
        ButtonBuilder bld(getWindow(),{begin_x + 210, begin_y}, "Rain");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(80)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x + 320, begin_y}, "Randomly");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(140)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addControll(bld.build());
    }

    begin_y += 100;
    {
        ButtonBuilder bld(getWindow(),{begin_x - 100, begin_y}, "Graphic");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(),{begin_x+60, begin_y}, "DrwaLine");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            width(120)->
            height(50)->
            carot()->
            enabled(true);

        addControll(bld.build());
    }


    begin_y += 100;
    {
        ButtonBuilder bld(getWindow(),{begin_x-80, begin_y}, "Back");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::OPTION_BACK))->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    ::DisplayInterface::onPreInitialize();
}


void TOptionDisplay::onDraw() {
    DisplayInterface::onDraw();
}

void TOptionDisplay::onClickedBack()
{
    DisplayInterface::onOK();
}



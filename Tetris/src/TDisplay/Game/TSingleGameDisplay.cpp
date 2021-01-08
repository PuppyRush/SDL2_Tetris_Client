//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TResource.h"
#include "SDL2EasyGUI/include/SEG_Type.h"
#include "SDL2EasyGUI/include/SEG_Event.h"
#include "SDL2EasyGUI/include/Button.h"
#include "../../TOption/TOptionManager.h"
#include "TSingleGameDisplay.h"
#include "SDL2EasyGUI/include/Button.h"

SDL_TETRIS
using namespace game_interface;
using namespace seg;
using namespace tetris_module;

TSingleGameDisplay::TSingleGameDisplay()
        : TGameDisplay()
{
    m_display = game_interface::toUType(TDisplay::Game);
}

void TSingleGameDisplay::onClickedStart(const void* click)
{


    TGameDisplay::onClickedStart(click);
}

void TSingleGameDisplay::onClickedSuspend(const void* click)
{

}

void TSingleGameDisplay::registerEvent()
{

    SEG_LBUTTONCLICK(game_interface::toUType(resource::GAME_START),
                     &TSingleGameDisplay::onClickedStart,
                     this);
}

void TSingleGameDisplay::onInitialize()
{
    seg::t_size begin_y = WINDOW_HEIGHT / 10 * 3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 5 * 3, begin_y}, "START");
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
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 5 * 3, begin_y}, "SUSPEND");
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
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 5 * 3, begin_y}, "EXIT");
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

void TSingleGameDisplay::onClose()
{

    TGameDisplay::onClose();
}

void TSingleGameDisplay::onCreate()
{

    TGameDisplay::onCreate();
}

void TSingleGameDisplay::onDraw()
{
    TGameDisplay::onDraw();
}
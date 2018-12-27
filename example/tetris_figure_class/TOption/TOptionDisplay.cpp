//
// Created by chaed on 18. 12. 18.
//

#include "TOptionDisplay.h"
#include "TControll/TStaticLabel.h"
#include "TControll/TButton.h"

SDL_TETRIS

void TOptionDisplay::_preInitialize()
{
    setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/4;
    t_size begin_x = WINDOW_WIDTH/3;



    {
        TControllBuilder bld({begin_x - 100, begin_y}, "SPEED");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(100)->
        height(50)->
        enabled(false);

        addMenu( TStaticLabel::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+60,begin_y }, "1");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        carot()->
        grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+120,begin_y }, "2");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+180,begin_y }, "3");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+240,begin_y }, "4");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+60,begin_y+60 }, "5");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+120,begin_y+60 }, "6");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+180,begin_y+60 }, "7");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }
    {
        TControllBuilder bld({begin_x+240,begin_y+60 }, "8");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(40)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(0);

        addMenu( TButton::getInstance(bld));
    }

    begin_y = WINDOW_HEIGHT/4 + 200;

    {
        TControllBuilder bld({begin_x-100,begin_y }, "MAP");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(80)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addMenu( TStaticLabel::getInstance(bld));
    }

    {
        TControllBuilder bld({begin_x+60,begin_y }, "Pyramid");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(120)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addMenu( TButton::getInstance(bld));
    }

    {
        TControllBuilder bld({begin_x+190,begin_y }, "Rain");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
            background_color(TColorCode::black)->
            width(80)->
            height(50)->
            enabled(true)->
            carot()->
            grouping(1);

        addMenu( TButton::getInstance(bld));
    }

}

void TOptionDisplay::_timer()
{

}

void TOptionDisplay::_draw()
{

}

void TOptionDisplay::_event(const SDL_Event* event)
{

}

std::shared_ptr<TDisplayInterface> TOptionDisplay::getInstance()
{
//boost::serialization::singleton<TMainLocalDisplay>::get_mutable_instance();
    static std::shared_ptr<TDisplayInterface> inst = std::shared_ptr<TDisplayInterface>(new TOptionDisplay{});
    return inst;
}


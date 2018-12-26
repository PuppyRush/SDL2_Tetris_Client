//
// Created by chaed on 18. 12. 18.
//

#include "TOptionDisplay.h"

SDL_TETRIS

void TOptionDisplay::_preInitialize()
{
    setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/4;
    t_size begin_x = WINDOW_WIDTH/3;

    TControllBuilder bld;

    bld.name("SPEED")->
        point({begin_x-100,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(100)->
        height(50)->
        enabled(false)->
        kind(TOption::StaticLabel)->
        add();

    bld.name("1")->
        point({begin_x+60,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("2")->
        point({begin_x+120,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("3")->
        point({begin_x+180,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("4")->
        point({begin_x+240,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();


    bld.name("5")->
        point({begin_x+60,begin_y+60 })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("6")->
        point({begin_x+120,begin_y+60 })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("7")->
        point({begin_x+180,begin_y+60 })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();

    bld.name("8")->
        point({begin_x+240,begin_y+60 })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(40)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(0)->
        add();


    begin_y = WINDOW_HEIGHT/4 + 200;

    bld.name("MAP")->
        point({begin_x-100,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(100)->
        height(50)->
        enabled(false)->
        kind(TOption::StaticLabel)->
        add();

    bld.name("Pyramid")->
        point({begin_x+60,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(120)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(1)->
        add();

    bld.name("Reverse pyramid")->
        point({begin_x+200,begin_y })->
        font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::white})->
        background_color(TColorCode::black)->
        width(220)->
        height(50)->
        enabled(true)->
        kind(TOption::StaticLabel)->
        carot()->
        grouping(1)->
        add();

    addMenu(bld);
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


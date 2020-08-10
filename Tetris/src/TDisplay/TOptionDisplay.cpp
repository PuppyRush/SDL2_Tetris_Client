//
// Created by chaed on 18. 12. 18.
//

#include "TOptionDisplay.h"
#include "TResource.h"
#include "SDL2EasyGUI/include/Button.h"
#include "SDL2EasyGUI/include/StaticLabel.h"

SDL_TETRIS
using namespace game_interface;
using namespace seg;
using namespace tetris_module;

TOptionDisplay::TOptionDisplay()
{
    m_display = game_interface::toUType(TDisplay::Option);
    m_mode = TLocalMode::All;
};

void TOptionDisplay::registerEvent()
{

    SEG_LBUTTONCLICK(seg::toUType(resource::OPTION_BACK), &TOptionDisplay::onClickedBack, this);
}

void TOptionDisplay::onInitialize()
{
    setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT / 4;
    t_size begin_x = WINDOW_WIDTH / 4;

    {
        StaticLabelBuilder bld(getWindow(), {begin_x - 100, begin_y}, "SPEED");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED))->
                backgroundColor(ColorCode::white)->
                width(130)->
                height(70)->
                enabled(false);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 60, begin_y}, "1");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_1))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 120, begin_y}, "2");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_2))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 180, begin_y}, "3");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_3))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 240, begin_y}, "4");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_4))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 60, begin_y + 60}, "5");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_5))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 120, begin_y + 60}, "6");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_6))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 180, begin_y + 60}, "7");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_7))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());

    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 240, begin_y + 60}, "8");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_SPEED_8))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(40)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(0);

        addControl(bld.build());
    }

    begin_y = WINDOW_HEIGHT / 4 + 200;

    {
        StaticLabelBuilder bld(getWindow(), {begin_x - 100, begin_y}, "MAP");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_MAP))->
                backgroundColor(ColorCode::white)->
                width(110)->
                height(80)->
                enabled(true)->
                carot()->
                grouping(1);

        addControl(bld.build());
    }

    {
        ButtonBuilder bld(getWindow(), {begin_x + 60, begin_y}, "Pyramid");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_MAP_PYRAMID))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(120)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(1);

        addControl(bld.build());
    }

    {
        ButtonBuilder bld(getWindow(), {begin_x + 210, begin_y}, "Rain");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_MAP_RAIN))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(80)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(1);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 320, begin_y}, "Randomly");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_MAP_RANDOMLY))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(140)->
                height(50)->
                enabled(true)->
                carot()->
                grouping(1);

        addControl(bld.build());
    }

    begin_y += 100;
    {
        ButtonBuilder bld(getWindow(), {begin_x - 100, begin_y}, "Graphic");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_GRAPHIC))->
                backgroundColor(ColorCode::white)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {begin_x + 60, begin_y}, "DrwaLine");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_GRAPHIC_DRAWLINE))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(120)->
                height(50)->
                carot()->
                enabled(true);

        addControl(bld.build());
    }

    begin_y += 130;
    {
        ButtonBuilder bld(getWindow(), {begin_x, begin_y}, "Back");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::OPTION_BACK))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }

    setWindowHeight(900);
    setWindowWidth(800);
    setWindowTitle("Option");

    ::DisplayInterface::onInitialize();
}

void TOptionDisplay::onDraw()
{
    DisplayInterface::onDraw();
}

void TOptionDisplay::onClickedBack(const void* click)
{
    DisplayInterface::onOk();
}

//
// Created by chaed on 18. 12. 18.
//

#include "SDL2EasyGUI/src/Controller/Button/Button.h"
#include "SDL2EasyGUI/include/DisplayController.h"

#include "TMultiMainDisplay.h"

#include "../TOptionDisplay.h"
#include "../../Common/TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

TMultiMainDisplay::TMultiMainDisplay(const sdleasygui::t_id displayId)
    :TMainDisplay(displayId)
{
    m_mode = TLocalMode::Online;
}

void TMultiMainDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(game_interface::toUType(resource::MAIN_MULTI_GAME_START_BUTTON),
                         &TMultiMainDisplay::onClickedEnterServer,
                         this);
    SEG_LBUTTONCLICK(game_interface::toUType(resource::MAIN_OPTION_BUTTON),
                         &TMultiMainDisplay::onClickedOption,
                         this);
    SEG_LBUTTONCLICK(game_interface::toUType(resource::MAIN_EXIT), &TMultiMainDisplay::onClickedBack, this);
}

void TMultiMainDisplay::onInitialize() {

    t_size begin_y = WINDOW_HEIGHT/3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 220, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(game_interface::toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
            width(240)->
            height(50)->
            borderBoundaryType(BorderBoundaryType::roundedAngle)->
            borderColor(ColorCode::silver)->
            borderThick(4)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/2 - 150, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(game_interface::toUType(resource::MAIN_OPTION_BUTTON))->
            backgroundColor(ColorCode::white)->
            borderBoundaryType(BorderBoundaryType::roundedAngle)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y+=80;
    {
        ButtonBuilder bld(getWindow(),{WINDOW_WIDTH/2 - 150, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(game_interface::toUType(resource::MAIN_EXIT))->
            backgroundColor(ColorCode::white)->
            borderBoundaryType(BorderBoundaryType::roundedAngle)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }

    TMainDisplay::onInitialize();
}

void TMultiMainDisplay::onDraw()
{
    TMainDisplay::onDraw();
}

void TMultiMainDisplay::onClickedOption(const void* click)
{



    TMainDisplay::onButtonClick(click);
}

void TMultiMainDisplay::onClickedEnterServer(const void* click)
{
    TMainDisplay::onButtonClick(click);
}

void TMultiMainDisplay::onClickedBack(const void* click)
{
    TMainDisplay::onOK();
}

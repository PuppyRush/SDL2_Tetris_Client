
//
// Created by chaed on 18. 12. 18.
//

#include "SDL2EasyGUI/src/Controller/Button.h"
#include "SDL2EasyGUI/src/Windows/DisplayController.h"

#include "TMultiMainDisplay.h"

#include "../TOptionDisplay.h"
#include "../../Common/TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

TMultiMainDisplay::TMultiMainDisplay()
:m_optionDisplay(std::make_shared<TOptionDisplay>()),
 m_enterServerDisplay(std::make_shared<TEnterServerDisplay>())
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
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(game_interface::toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
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
            id(game_interface::toUType(resource::MAIN_OPTION_BUTTON))->
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
            id(game_interface::toUType(resource::MAIN_EXIT))->
            backgroundColor(ColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onInitialize();
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

    m_optionDisplay->setWindowHeight(WINDOW_HEIGHT);
    m_optionDisplay->setWindowWidth(WINDOW_WIDTH);
    m_optionDisplay->setWindowTitle("Option Dialog");
    m_optionDisplay->modaless(m_optionDisplay);
    m_optionDisplay->waitModaless();
    //DisplayInterface::onOK();
}

void TMultiMainDisplay::onClickedEnterServer()
{
    m_enterServerDisplay->setWindowHeight(300);
    m_enterServerDisplay->setWindowWidth(300);
    m_enterServerDisplay->setWindowTitle("Input Your Nickname");
    m_enterServerDisplay->modal(m_enterServerDisplay);

    DisplayInterface::onOK();
}

void TMultiMainDisplay::onClickedBack()
{
    TDisplayInterface::onClose();
}

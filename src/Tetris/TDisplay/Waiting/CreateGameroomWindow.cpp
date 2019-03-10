//
// Created by chaed on 19. 3. 8.
//

#include "CreateGameroomWindow.h"

#include "SDLEasyGUI/Controller/EditLabel.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/SEG_TypeTraits.h"
#include "../../Common/TResource.h"

using namespace std;
using namespace sdleasygui;
using namespace game_interface;

void CreateGameroomWindow::registerEvent()
{
    event_buttonClick(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_OK), std::bind(&CreateGameroomWindow::onOK, this));
    event_buttonClick(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_CANCEL), std::bind(&CreateGameroomWindow::onCancel, this));
}

void CreateGameroomWindow::onInitialize()
{
    {
        EditLabelBuilder bld(getWindow(), {100,50}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 20, ColorCode::black})->
            backgroundColor(ColorCode::white)->
            id(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_GAMEROOMNAME))->
            width(150)->
            height(50)->
            borderColor(ColorCode::dimgray)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {50,120}, "OK");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_OK))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    {
        ButtonBuilder bld(getWindow(), {200,120}, "CANCEL");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 28, ColorCode::white})->
            backgroundColor(ColorCode::dimgray)->
            id(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_CANCEL))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onInitialize();
}

void CreateGameroomWindow::onClose()
{
    const auto ctl = std::static_pointer_cast<EditLabel>(getControll(tetris::resource::WAITINGROOM_CREATE_GAMEROOMNAME));
    m_roomname = ctl->getString();

    DisplayInterface::onClose();
}

void CreateGameroomWindow::onDraw()
{
    DisplayInterface::onDraw();
}

void CreateGameroomWindow::onOK()
{
    DisplayInterface::onOK();
}

void CreateGameroomWindow::onCancel()
{
    DisplayInterface::onCancel();
}
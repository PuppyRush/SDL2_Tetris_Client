//
// Created by chaed on 19. 3. 8.
//

#include "TCreateGameroomWindow.h"

#include "SDL2EasyGUI/src/Controller/EditLabel.h"
#include "SDL2EasyGUI/src/Controller/Button.h"
#include "SDL2EasyGUI/src/SEG_TypeTraits.h"
#include "../../Common/TResource.h"

using namespace std;
using namespace sdleasygui;
using namespace game_interface;

SDL_TETRIS

void TCreateGameroomWindow::registerEvent()
{
    SEG_LBUTTONCLICK(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_OK),
                         &TCreateGameroomWindow::onOK, this);
    SEG_LBUTTONCLICK(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_CANCEL),
                         &TCreateGameroomWindow::onCancel, this);
}

void TCreateGameroomWindow::onInitialize()
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
            width(120)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onInitialize();
}

void TCreateGameroomWindow::onClose()
{
    const auto ctl = dynamic_cast<EditLabel*>(getControll(tetris::resource::WAITINGROOM_CREATE_GAMEROOMNAME));
    m_roomname = ctl->getString();

    DisplayInterface::onClose();
}

void TCreateGameroomWindow::onDraw()
{
    DisplayInterface::onDraw();
}

void TCreateGameroomWindow::onOK()
{
    DisplayInterface::onOK();
}

void TCreateGameroomWindow::onCancel()
{
    DisplayInterface::onCancel();
}
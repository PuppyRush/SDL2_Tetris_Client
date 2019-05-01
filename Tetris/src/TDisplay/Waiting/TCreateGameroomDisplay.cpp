//
// Created by chaed on 19. 3. 8.
//

#include "TCreateGameroomDisplay.h"

#include "SDL2EasyGUI/include/EditLabel.h"
#include "SDL2EasyGUI/include/Button.h"
#include "SDL2EasyGUI/include/SEG_TypeTraits.h"
#include "TResource.h"

using namespace std;
using namespace sdleasygui;
using namespace game_interface;

SDL_TETRIS

TCreateGameroomDisplay::TCreateGameroomDisplay(const sdleasygui::t_id displayId)
        : TDisplayInterface(displayId)
{

}

void TCreateGameroomDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_OK),
                     &TCreateGameroomDisplay::onClickOk, this);
    SEG_LBUTTONCLICK(sdleasygui::toUType(tetris::resource::WAITINGROOM_CREATE_CANCEL),
                     &TCreateGameroomDisplay::onClickCancel, this);
}

void TCreateGameroomDisplay::onInitialize()
{
    {
        EditLabelBuilder bld(getWindow(), {100, 50}, "");
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
        ButtonBuilder bld(getWindow(), {50, 120}, "OK");
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
        ButtonBuilder bld(getWindow(), {200, 120}, "CANCEL");
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

    TDisplayInterface::onInitialize();
}

void TCreateGameroomDisplay::onClose()
{
    const auto ctl = getControll<EditLabel>(tetris::resource::WAITINGROOM_CREATE_GAMEROOMNAME);
    m_roomname = ctl->getString();

    TDisplayInterface::onClose();
}

void TCreateGameroomDisplay::onDraw()
{
    TDisplayInterface::onDraw();
}

void TCreateGameroomDisplay::onClickOk(const void*)
{
    TDisplayInterface::onOK();
}

void TCreateGameroomDisplay::onClickCancel(const void*)
{
    TDisplayInterface::onCancel();
}
//
// Created by chaed on 19. 2. 14.
//


#include "TEnterServerDisplay.h"
#include "../../Common/TResource.h"

#include "../../TObject/TPlayer.h"
#include "GameInterface/src/Online/PacketQueue.h"
#include "SDL2EasyGUI/src/Controller/EditLabel.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

void TEnterServerDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::ENTERSERVER_OK),&TEnterServerDisplay::onClickedEnterServer, this);
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::ENTERSERVER_BACK),&TEnterServerDisplay::onClickedBack, this);
}

void TEnterServerDisplay::onInitialize() {

    t_size begin_y = getWindowHeight()/3;
    {
        EditLabelBuilder bld(getWindow(), {getWindowWidth() / 2 - 120, begin_y}, "Player");
        bld.id(sdleasygui::toUType(resource::ENTERSERVER_ID))->
            fontColor(ColorCode::black)->
            width(240)->
            height(50)->
            backgroundColor(ColorCode::white)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {getWindowWidth() / 2 - 120, begin_y}, "ENTER");
        bld.id(sdleasygui::toUType(resource::ENTERSERVER_OK))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    {
        ButtonBuilder bld(getWindow(), {getWindowWidth() / 2 , begin_y}, "BACK");
        bld.id(sdleasygui::toUType(resource::ENTERSERVER_BACK))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    ::DisplayInterface::onInitialize();
}

void TEnterServerDisplay::onClickedEnterServer(const void* click)
{
    auto player = TPlayer::getInstance();
    const  auto btn = getControll<EditLabel>(resource::ENTERSERVER_ID);

    assert(btn != nullptr );
    player->setUserName(btn->getString());

    DisplayInterface::onButtonClick(click);
}


void TEnterServerDisplay::onClickedBack(const void* click)
{
    DisplayInterface::onOK();
}
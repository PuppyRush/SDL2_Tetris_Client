//
// Created by chaed on 19. 2. 14.
//


#include "TEnterServerDisplay.h"
#include "../../Common/TResource.h"
#include "../Waiting/TWaitingRoomDisplay.h"
#include "../../TObject/TPlayer.h"
#include "GameInterface/Online/PacketQueue.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

void TEnterServerDisplay::registerEvent()
{
    event_buttonClick(toUType(resource::ENTERSERVER_OK), std::bind(&TEnterServerDisplay::onClickedEnterServer, this));
    event_buttonClick(toUType(resource::ENTERSERVER_BACK), std::bind(&TEnterServerDisplay::onClickedBack, this));
}

void TEnterServerDisplay::onPreInitialize() {

    t_size begin_y = WINDOW_HEIGHT/3;
    {
        EditLabelBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "Player");
        bld.id(toUType(resource::ENTERSERVER_ID))->
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
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "ENTER");
        bld.id(toUType(resource::ENTERSERVER_OK))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "BACK");
        bld.id(toUType(resource::ENTERSERVER_BACK))->
            width(100)->
            height(50)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        addControll(bld.build());
    }

    ::DisplayInterface::onPreInitialize();
}

void TEnterServerDisplay::onClickedEnterServer()
{
    auto player = TPlayer::getInstance();
    const auto& btn = getControll(resource::ENTERSERVER_OK);
    assert(btn != nullptr );

    player->setUserName(btn->getName());
    player->connectServer();

    game_interface::PacketQueue::getInstance().attach(player);

    auto dlg = std::make_shared<TWaitingRoomDisplay>();
    dlg->modal();
}


void TEnterServerDisplay::onClickedBack()
{
    DisplayInterface::onClose();
}
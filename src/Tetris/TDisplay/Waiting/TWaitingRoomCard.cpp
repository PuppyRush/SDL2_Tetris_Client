//
// Created by chaed on 19. 2. 15.
//

#include "TWaitingRoomCard.h"
#include "SDLEasyGUI/Controller/EditLabel.h"
#include "../../Common/TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;

TWaitingRoomCard::TWaitingRoomCard(TWaitingRoomCardBuilder& bld)
    :Border(bld), m_cardBasic(bld.m_cardBasic)
{
    bld.kind(sdleasygui::ControllKind::ListBox);
}

void TWaitingRoomCard::onDraw()
{
    Border::onDraw();
}

void TWaitingRoomCard::initialize()
{

    t_size begin_y = getPoint().y+20;
    {
        EditLabelBuilder bld(getWindow(), {getPoint().x+20, begin_y}, "Player");
        //bld.id(toUType(resource::ENTERSERVER_ID))->
        bld.fontColor(ColorCode::black)->
            width(150)->
            height(30)->
            backgroundColor(ColorCode::white)->
            borderColor(ColorCode::white)->
            borderThick(2)->
            enabled(true);

        //addControll(bld.build());
    }

    Border::initialize();
}


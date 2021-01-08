//
// Created by chaed on 19. 2. 15.
//

#include "TWaitingRoomCard.h"
#include "SDL2EasyGUI/include/EditLabel.h"
#include "TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace seg;

TWaitingRoomCard::TWaitingRoomCard(TWaitingRoomCardBuilder& bld)
        : Border(bld), m_cardBasic(bld.m_cardBasic)
{
    bld.kind(seg::ControlKind::ListBox);
}

void TWaitingRoomCard::onDraw()
{
    Border::onDraw();
}

void TWaitingRoomCard::initialize()
{

    seg::t_size begin_y = getPoint().y + 20;
    {
        EditLabelBuilder bld(getWindow(), {getPoint().x + 20, begin_y}, "Player");
        //bld.id(toUType(resource::ENTERSERVER_ID))->
        bld.fontColor(ColorCode::black)->
                width(150)->
                height(30)->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        //addControl(bld.build());
    }

    Border::initialize();
}


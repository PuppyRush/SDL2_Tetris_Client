//
// Created by chaed on 19. 2. 15.
//

#include "TWaitingRoomCard.h"

SDL_TETRIS

TWaitingRoomCard::TWaitingRoomCard(TWaitingRoomCardBuilder& bld)
    :Border(bld)
{
    bld.kind(sdleasygui::ControllKind::ListBox);
}

void TWaitingRoomCard::onDraw()
{
    Border::onDraw();
}

void TWaitingRoomCard::initialize()
{
    Border::initialize();
}


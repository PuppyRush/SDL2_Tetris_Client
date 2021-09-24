//
// Created by chaed on 19. 1. 13.
//
#include <ctime>

#include "TPlayerBox.h"
#include "Tetris/include/TFigureBuilder.h"

SDL_TETRIS

using namespace std;
using namespace tetris_module;
using namespace game_interface;
using namespace game_interface::packet;
using namespace seg;

TPlayerBox::TPlayerBox(const BoxItemBuilder& bld, const TPlayer& player)
    :TPlayer(player), BoxItem(bld)
{

}

TPlayerBox::TPlayerBox(BoxItemBuilder&& bld, TPlayer&& player)
    : TPlayer(player), BoxItem(bld)
{

}


//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_CLIENT_TPlayerBOX_H
#define TETRIS_CLIENT_TPlayerBOX_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <cassert>

#include "SDL2EasyGUI/include/BoxItem.h"
#include "GameInterface/include/Packet.h"
#include "../../TObject/TPlayer.h"

SDL_TETRIS_BEGIN

class TPlayerBox final : public TPlayer, public seg::BoxItem
{
public:

    TPlayerBox(const seg::BoxItemBuilder& bld, const TPlayer& player);

    TPlayerBox(seg::BoxItemBuilder&& bld, TPlayer&& player);

    virtual ~TPlayerBox() = default;

    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent* motion) override
    {

    }

    virtual void onDraw() override
    {

    }

};

SDL_TETRIS_END

#endif //TETRIS_CLIENT_TPlayerBox_H

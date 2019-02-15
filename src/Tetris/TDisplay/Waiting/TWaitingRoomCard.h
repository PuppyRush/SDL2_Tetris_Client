//
// Created by chaed on 19. 2. 15.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H

#include "SDLEasyGUI/Controller/Border.h"
#include "SDLEasyGUI/Controller/StaticLabel.h"
#include "../Game/TMultiGameRoomDisplay.h"

SDL_TETRIS_BEGIN

class TWaitingRoomCard final : public Border
{

    virtual void onDraw() override final;

private:

    StaticLabel m_name;
    StaticLabel m_partyNumber;
    StaticLabel m_state;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMCARD_H

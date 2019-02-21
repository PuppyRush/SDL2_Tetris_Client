//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H
#define TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

#include "SDLEasyGUI/Windows/DisplayInterface.h"
#include "TWaitingRoomCard.h"

SDL_TETRIS_BEGIN

class TWaitingRoomDisplay : public DisplayInterface{

public:
    virtual void updateObserver(const Observer&, const game_interface::Packet &) override final {}

private:

    std::vector<TWaitingRoomCard> m_gamerooms;

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TWAITINGROOMDISPLAY_H

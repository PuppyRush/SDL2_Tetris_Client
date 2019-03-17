//
// Created by chaed on 19. 3. 10.
//

#ifndef PROJECT_TTETRISDISPLAYINTERFACE_H
#define PROJECT_TTETRISDISPLAYINTERFACE_H

#include "../Common/THeader.h"
#include "SDL2EasyGUI/src/Windows/DisplayInterface.h"
#include "GameInterface/src/SubScription/Observer.h"
#include "GameInterface/src/Online/Packet.h"
#include "GameInterface/src/Online/PacketQueue.h"

SDL_TETRIS_BEGIN

class TDisplayInterface : public sdleasygui::DisplayInterface, public game_interface::Observer
{

public:
    virtual ~TDisplayInterface() = default;

protected:
    virtual void updateObserver(const game_interface::Packet& )
    {
    }

    virtual void postCreate()
    {
        game_interface::PacketQueue::getInstance().attach(this);
    }

    virtual void postDestroy()
    {
        game_interface::PacketQueue::getInstance().detach( this->getUnique());
    }

    virtual bool validId(const sdleasygui::t_id id) noexcept
    {
        return getWindowID() == id;
    }

};

SDL_TETRIS_END

#endif //PROJECT_TTETRISDISPLAYINTERFACE_H

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

    using unique_type = typename sdleasygui::DisplayInterface::unique_type ;

    virtual ~TDisplayInterface()
    {
    }

protected:

    TDisplayInterface()
    {}

    virtual void updateObserver(const game_interface::Packet& )
    {
    }

    virtual void postCreate(display_ptr display) override
    {
        game_interface::PacketQueue::getInstance().attach(std::dynamic_pointer_cast<TDisplayInterface>(display) );
    }

    virtual void postDestroy(const unique_type unique) override
    {
        game_interface::PacketQueue::getInstance().detach( unique);
    }

    virtual void onClose() override
    {
        postDestroy(this->getUnique());
        DisplayInterface::onClose();
    }

    virtual bool validId(const sdleasygui::t_id id) noexcept
    {
        return getWindowID() == id;
    }

private:
    virtual const std::string_view& getUniqueName() const override {}
    virtual Json::Value toJson() const override{}
    virtual void fromJson(const Json::Value& json) override {}

};

SDL_TETRIS_END

#endif //PROJECT_TTETRISDISPLAYINTERFACE_H

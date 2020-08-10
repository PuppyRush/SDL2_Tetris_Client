//
// Created by chaed on 19. 3. 10.
//

#ifndef PROJECT_TTETRISDISPLAYINTERFACE_H
#define PROJECT_TTETRISDISPLAYINTERFACE_H

#include "THeader.h"
#include "TResource.h"
#include "SDL2EasyGUI/include/DisplayInterface.h"
#include "GameInterface/include/Observer.h"
#include "GameInterface/include/Packet.h"
#include "GameInterface/include/PacketQueue.h"

SDL_TETRIS_BEGIN

class TDisplayInterface : public seg::DisplayInterface, public game_interface::Observer
{

public:

    using unique_type = typename seg::DisplayInterface::unique_type;

    virtual ~TDisplayInterface()
    {}

    virtual const seg::t_id getDisplayId() const noexcept = 0;

protected:

    TDisplayInterface() = default;

    virtual void updateObserver(const game_interface::packet::Packet&)
    {
    }

    virtual void postCreate(display_ptr display) override
    {
        game_interface::PacketQueue::getInstance().attach(std::dynamic_pointer_cast<TDisplayInterface>(display));
    }

    virtual void postDestroy(const unique_type unique) override
    {
        game_interface::PacketQueue::getInstance().detach(unique);
    }

    virtual void onClose() override
    {
        postDestroy(this->getUnique());
        DisplayInterface::onClose();
    }

    virtual bool validId(const seg::t_id id) noexcept
    {
        return getWindowID() == id;
    }

private:
    virtual const std::string_view& getUniqueName() const override
    {
        assert(0);
        return game_interface::NAME_NULL;
    }

    virtual Json::Value toJson() const override final
    {
        assert(0);
        return Json::Value{};
    }

    virtual void fromJson(const Json::Value& json) override final
    {
        assert(0);
    }

    
};

SDL_TETRIS_END

#endif //PROJECT_TTETRISDISPLAYINTERFACE_H

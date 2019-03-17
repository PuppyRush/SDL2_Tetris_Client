//
// Created by chaed on 19. 3. 13.
//

#ifndef PROJECT_TETRISWAITINGROOM_H
#define PROJECT_TETRISWAITINGROOM_H

#include <boost/serialization/singleton.hpp>
#include "GameInterface/src/Object/WaitingRoom.h"
#include "../Common/TDefine.h"

SDL_TETRIS_BEGIN

class TWaitingRoom : public game_interface::WaitingRoom , private boost::serialization::singleton<TWaitingRoom>
{
public:
    friend class boost::serialization::singleton<TWaitingRoom>;

    static std::shared_ptr<TWaitingRoom> getInstance() {
        static auto inst = std::shared_ptr<TWaitingRoom>
            (&boost::serialization::singleton<TWaitingRoom>::get_mutable_instance());
        return inst;
    }

protected:
    virtual void postEnter(player_ptr ply) override;
    virtual void postExit(const unique_type unique) override;
    virtual void postAddedGameRoom(room_ptr room) override;
    virtual void postRemovedGameRoom(const unique_type unique) override;

private:
    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}
    virtual void updateObserver(const game_interface::Packet& ) override;

};

SDL_TETRIS_END

#endif //PROJECT_TETRISWAITINGROOM_H

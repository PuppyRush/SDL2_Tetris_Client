//
// Created by chaed on 19. 3. 23.
//

#ifndef PROJECT_TGAMEROOM_H
#define PROJECT_TGAMEROOM_H


#include <boost/serialization/singleton.hpp>
#include "GameInterface/src/Object/GameRoom.h"
#include "../Common/TDefine.h"

SDL_TETRIS_BEGIN

class TGameRoom : public game_interface::GameRoom , private boost::serialization::singleton<TGameRoom>{

public:

    friend class boost::serialization::singleton<TGameRoom>;

    static std::shared_ptr<TGameRoom> getInstance() {
        static auto inst = std::shared_ptr<TGameRoom>
            (&boost::serialization::singleton<TGameRoom>::get_mutable_instance());
        return inst;
    }

    virtual void postEnter(player_ptr ply) override;
    virtual void postExit(const unique_type unique) override;

private:
    virtual Json::Value toJson() const override {}
    virtual const std::string_view& getUniqueName() const override {}
    virtual void updateObserver(const game_interface::Packet& ) override;

};

SDL_TETRIS_END

#endif //PROJECT_TGAMEROOM_H

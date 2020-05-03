//
// Created by chaed on 19. 3. 23.
//

#ifndef PROJECT_TGAMEROOM_H
#define PROJECT_TGAMEROOM_H

#include <array>
#include <boost/serialization/singleton.hpp>

#include "GameInterface/include/GameRoom.h"

#include "TDefine.h"
#include "TPlayer.h"

SDL_TETRIS_BEGIN

class TGameRoom : public game_interface::GameRoom
{

public:

    using player_ptr = std::shared_ptr<TPlayer>;
    using board_ptr = std::shared_ptr<tetris_module::TFigureController>;

    TGameRoom() = default;

    static std::shared_ptr<TGameRoom> getInstance()
    {
        static auto inst = std::make_shared<TGameRoom>();
        return inst;
    }

    virtual void postEnter(const GameRoom::player_ptr&) override;

    virtual void postExit(const GameRoom::player_ptr&) override;

    virtual void fromJson(const Json::Value& json);

    virtual void initialize() override;

    virtual void destory() override;

private:


    virtual const std::string_view& getUniqueName() const override
    { return game_interface::NAME_GAMEROOM; }

    virtual void updateObserver(const game_interface::packet::Packet&) override;

};

SDL_TETRIS_END

#endif //PROJECT_TGAMEROOM_H

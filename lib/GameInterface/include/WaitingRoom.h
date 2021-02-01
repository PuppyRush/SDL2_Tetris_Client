//
// Created by chaed on 19. 2. 8.
//

#ifndef GAMEINTERFACE_WAITINGROOM_H
#define GAMEINTERFACE_WAITINGROOM_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Room.h"

namespace game_interface {

class WaitingRoom : public Room
{

public:
    using player_ptr = Room::player_ptr;
    using room_ptr = Room::room_ptr;
    using unique_type = Room::unique_type;
    using room_container = std::vector<room_ptr>;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    virtual void exit(const unique_type unique) override;

    virtual void addGameRoom(const room_ptr& room);

    virtual void removeGameRoom(const unique_type unique);

    const room_ptr& getGameroom(const unique_type gameroomUnique) const;

    virtual const bool existGameRoom(const unique_type unique) const noexcept;

    inline const room_container& getGameRoomContiner() const noexcept
    { return m_rooms; }

    virtual void updateObserver(const packet::Packet&) = 0;

protected:
    WaitingRoom() = default;

    virtual void postAddedGameRoom(const room_ptr& room) = 0;

    virtual void postRemovedGameRoom(const unique_type unique) = 0;

    virtual void postEnter(const player_ptr&) = 0;

    virtual void postExit(const player_ptr&) = 0;

private:
    std::vector<room_ptr> m_rooms;
    std::mutex m_roomMutex;
};

}

#endif //SDL2EASYGUI_WAITINGROOM_H

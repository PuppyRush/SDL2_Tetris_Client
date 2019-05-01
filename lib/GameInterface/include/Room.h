//
// Created by chaed on 19. 1. 16.
//

#ifndef OBJECT_ROOM_H
#define OBJECT_ROOM_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <string>
#include <vector>
#include <mutex>

#include "GameInterface/src/SubScription/Observer.h"
#include "Player.h"

namespace game_interface {

class Room : public Observer
{
public:
    using room_ptr = std::shared_ptr<Room>;
    using player_ptr = std::shared_ptr<Player>;
    using player_container = std::vector<player_ptr>;

    explicit Room();

    inline size_t getFullCount() const noexcept
    { return m_fullCount; }

    inline void setFullCount(const size_t c)
    { m_fullCount = c; }

    inline t_id getRoomNumber() const noexcept
    { return m_roomnumber.load(); }

    inline void setRoomNumber(const t_id id)
    { m_roomnumber.exchange(id); }

    inline std::string getRoomName() const noexcept
    { return m_roomname; }

    void setRoomName(const std::string& name);

    inline const player_container& getPlayerContainer() const noexcept
    { return m_players; }

    virtual void enter(player_ptr ply);

    virtual void exit(const unique_type unique);

    virtual bool exist(const unique_type unique) const noexcept;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    virtual void initialize();

    virtual void updateObserver(const Packet&) = 0;

protected:
    virtual void postEnter(const player_ptr& ply) = 0;

    virtual void postExit(const player_ptr& ply) = 0;

    virtual void destory();

private:

    size_t m_fullCount = ROOM_FULLCOUNT;
    std::mutex m_mutex;
    std::string m_roomname;
    t_id_atomic m_roomnumber;
    player_container m_players;

};

}

#endif //TETRIS_FIGURE_CLASS_TROOM_H

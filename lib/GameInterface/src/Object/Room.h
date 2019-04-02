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

#include "../SubScription/Observer.h"
#include "Player.h"

namespace game_interface {

class Room : public Observer {
public:
    using room_ptr = std::shared_ptr<Room>;
    using player_ptr = std::shared_ptr<Player>;
    using player_container = std::vector<player_ptr>;

    Room();

    inline const t_id getRoomNumber() const noexcept { return m_roomnumber.load();}
    inline void setRoomNumber(const t_id id) { m_roomnumber.exchange(id);}

    inline const std::string getRoomName() const noexcept { return m_roomname;}
    void setRoomName(const std::string &name);
    inline const player_container& getPlayerContainer() const noexcept { return m_players;}

    virtual void enter(player_ptr ply) ;
    virtual void exit(const unique_type unique);
    virtual const bool exist(const unique_type unique) const noexcept;

    virtual void updateObserver(const Packet& ) =0;

    virtual Json::Value toJson() const override;
    virtual void fromJson(const Json::Value& json);

protected:
    virtual void postEnter(player_ptr ply) = 0;
    virtual void postExit(const unique_type unique) = 0;

private:

    std::mutex m_mutex;
    std::string m_roomname;
    t_id_atomic m_roomnumber;
    player_container m_players;

};

}

#endif //TETRIS_FIGURE_CLASS_TROOM_H

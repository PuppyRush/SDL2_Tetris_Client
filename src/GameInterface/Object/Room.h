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

#include "Observer.h"
#include "Player.h"

namespace game_interface {

class Room : public Observer {
public:
    using room_ptr = std::shared_ptr<Room>;
    using player_ptr = std::shared_ptr<Player>;
    using player_container = std::vector<player_ptr>;

    Room();

    inline const t_id getRoomNumber() { return m_roomnumber.load();}
    inline const std::string getRoomName() { return m_roomname;}
    void setRoomName(const std::string &name);
    inline const player_container& getContainer(){ return m_players;}

    virtual void updateObserver(const Packet& ) =0;
    virtual void enter(player_ptr ply) ;
    virtual void exit(const unique_type unique);

private:
    std::mutex m_mutex;
    std::string m_roomname;
    t_id_atomic m_roomnumber;
    player_container m_players;
};

}

#endif //TETRIS_FIGURE_CLASS_TROOM_H

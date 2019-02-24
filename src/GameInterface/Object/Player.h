//
// Created by chaed on 19. 1. 13.
//

#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Observer.h"

namespace game_interface {

class Player : public Observer {
public:

    Player() = default;
    virtual ~Player() = default;

    inline const std::string getUserName() const noexcept { return m_name; }
    inline void setUserName(const std::string &name) { m_name = name; }

private:
    std::string m_name;
};

}

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

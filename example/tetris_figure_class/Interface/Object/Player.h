//
// Created by chaed on 19. 1. 13.
//

#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include "Common/TDefine.h"
#include "TGame/TFigureBoard.h"

#include "Object.h"
#include "TGame/TScore.h"

SDL_TETRIS_BEGIN

class Player : public Object
{
public:

    Player() = default;
    virtual ~Player() = default;

    inline const std::string getUserName() const noexcept { return m_name; }
    inline void setName(const std::string name) { m_name = name; }

private:
    std::string m_name;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

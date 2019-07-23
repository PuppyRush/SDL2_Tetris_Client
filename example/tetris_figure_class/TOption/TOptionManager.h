//
// Created by chaed on 18. 12. 26.
//

#ifndef TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H
#define TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H

#include <memory>

#include "Common/THeader.h"

SDL_TETRIS_BEGIN

class TOptionManager final
{

public:


    TSpeed getSpeed() const;
    void setSpeed(TSpeed m_speed);

    TMap getMap() const;
    void setMap(TMap m_map);

    bool isEnabledGhostMode() const;
    void setEnabledGhostMode(bool m_enabledGhostMode);

    bool isEnabledCombo() const;
    void setEnabledCombo(bool m_enabledCombo);

    bool isDrawLine() const;
    void setDrawLine(bool drawline);

    static std::shared_ptr<TOptionManager> getInstance();

private:
    TSpeed m_speed = TSpeed::_3;
    TMap    m_map = TMap::None;
    bool m_enabledGhostMode = false;
    bool m_enabledCombo = false;

    //graphic
    bool m_drawline;

    TOptionManager() = default;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H

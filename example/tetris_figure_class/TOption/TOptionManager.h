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

    TSpeed m_speed = TSpeed::_3;
    TMap    m_map = TMap::None;
    bool m_enabledGhostMode = false;
    bool m_enabledCombo = false;

    TSpeed getM_speed() const;
    void setM_speed(TSpeed m_speed);

    TMap getM_map() const;
    void setM_map(TMap m_map);

    bool isM_enabledGhostMode() const;
    void setM_enabledGhostMode(bool m_enabledGhostMode);

    bool isM_enabledCombo() const;
    void setM_enabledCombo(bool m_enabledCombo);

    static std::shared_ptr<TOptionManager> getInstance();

private:

    TOptionManager() = default;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H

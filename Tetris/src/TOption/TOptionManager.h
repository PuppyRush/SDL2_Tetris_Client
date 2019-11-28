//
// Created by chaed on 18. 12. 26.
//

#ifndef TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H
#define TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <memory>

#include "TDefine.h"
#include "Tetris/include/TProperty.h"

SDL_TETRIS_BEGIN

class TOptionManager : private boost::serialization::singleton<TOptionManager>
{
public:

    friend class boost::serialization::singleton<TOptionManager>;

	TOptionManager() = default;

	virtual ~TOptionManager() = default;

    tetris_module::TSpeed getSpeed() const;

    void setSpeed(tetris_module::TSpeed m_speed);

    tetris_module::TMap getMap() const;

    void setMap(tetris_module::TMap m_map);

    bool isEnabledGhostMode() const;

    void setEnabledGhostMode(bool m_enabledGhostMode);

    bool isEnabledCombo() const;

    void setEnabledCombo(bool m_enabledCombo);

    bool isDrawLine() const;

    void setDrawLine(bool drawline);

    static std::shared_ptr<TOptionManager> getInstance()
    {
        static auto inst = std::shared_ptr<TOptionManager>
                (&boost::serialization::singleton<TOptionManager>::get_mutable_instance());
        return inst;
    }

private:
    tetris_module::TSpeed m_speed = tetris_module::TSpeed::_3;
    tetris_module::TMap m_map = tetris_module::TMap::None;
    bool m_enabledGhostMode = false;
    bool m_enabledCombo = false;

    //graphic
    bool m_drawline;


};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TOPTIONMANAGER_H

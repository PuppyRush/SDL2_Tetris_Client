//
// Created by chaed on 18. 12. 26.
//

#include "TOptionManager.h"

SDL_TETRIS

std::shared_ptr<TOptionManager> TOptionManager::getInstance()
{
    static auto inst = std::shared_ptr<TOptionManager>(new TOptionManager());
    return inst;
}

TSpeed TOptionManager::getSpeed() const {
    return m_speed;
}

void TOptionManager::setSpeed(TSpeed m_speed) {
    TOptionManager::m_speed = m_speed;
}

TMap TOptionManager::getMap() const {
    return m_map;
}

void TOptionManager::setMap(TMap m_map) {
    TOptionManager::m_map = m_map;
}

bool TOptionManager::isEnabledGhostMode() const {
    return m_enabledGhostMode;
}

void TOptionManager::setEnabledGhostMode(bool m_enabledGhostMode) {
    TOptionManager::m_enabledGhostMode = m_enabledGhostMode;
}

bool TOptionManager::isEnabledCombo() const {
    return m_enabledCombo;
}

void TOptionManager::setEnabledCombo(bool m_enabledCombo) {
    TOptionManager::m_enabledCombo = m_enabledCombo;
}

bool TOptionManager::isDrawLine() const
{
    return TOptionManager::m_drawline;
}

void TOptionManager::setDrawLine(bool drawline)
{
    TOptionManager::m_drawline = drawline;
}
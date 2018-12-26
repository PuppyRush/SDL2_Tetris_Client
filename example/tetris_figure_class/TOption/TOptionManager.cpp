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

TSpeed TOptionManager::getM_speed() const {
    return m_speed;
}

void TOptionManager::setM_speed(TSpeed m_speed) {
    TOptionManager::m_speed = m_speed;
}

TMap TOptionManager::getM_map() const {
    return m_map;
}

void TOptionManager::setM_map(TMap m_map) {
    TOptionManager::m_map = m_map;
}

bool TOptionManager::isM_enabledGhostMode() const {
    return m_enabledGhostMode;
}

void TOptionManager::setM_enabledGhostMode(bool m_enabledGhostMode) {
    TOptionManager::m_enabledGhostMode = m_enabledGhostMode;
}

bool TOptionManager::isM_enabledCombo() const {
    return m_enabledCombo;
}

void TOptionManager::setM_enabledCombo(bool m_enabledCombo) {
    TOptionManager::m_enabledCombo = m_enabledCombo;
}

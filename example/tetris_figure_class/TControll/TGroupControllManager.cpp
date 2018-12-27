//
// Created by chaed on 18. 12. 28.
//

#include "TGroupControllManager.h"

SDL_TETRIS

std::shared_ptr<TGroupControllManager> TGroupControllManager::getInstance()
{
    static auto inst = std::shared_ptr<TGroupControllManager>(new TGroupControllManager());
    return inst;
}
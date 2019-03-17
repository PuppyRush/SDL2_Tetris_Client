//
// Created by chaed on 19. 2. 24.
//

#include "ManagerController.h"

using namespace game_interface;

void ManagerController::updateObserver(const game_interface::Packet& packet)
{
    auto container = getContainer();
    for(auto& mng : container)
    {
        mng->updateObserver(packet);
    }
}

void ManagerController::postDetach(_Base::unique_type unique)
{
    auto container = getContainer();
    for(auto& mng : container)
    {
        mng->detach(unique);
    }
}

//
// Created by chaed on 19. 2. 24.
//

#include "ManagerController.h"

using namespace game_interface;
using namespace game_interface::packet;

void ManagerController::updateObserver(const Packet& packet)
{
    auto container = getContainer();
    for (auto& mng : container) {
        mng->updateObserver(packet);
    }
}

void ManagerController::postDetach(const unique_type unique)
{
    auto container = getContainer();
    for (auto& mng : container) {
        mng->detach(unique);
    }
}

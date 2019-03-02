//
// Created by chaed on 19. 2. 24.
//

#include "ManagerController.h"

using namespace server;

void ManagerController::updateObserver(const game_interface::Packet& packet)
{
    auto container = getContainer();
    for(auto& mng : container)
    {
        mng->updateObserver(packet);
    }

}

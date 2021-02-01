//
// Created by chaed on 19. 3. 1.
//

#ifndef GAMEINTERFACE_MANAGERINTERFACE_H
#define GAMEINTERFACE_MANAGERINTERFACE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Observer.h"

namespace game_interface {

class ManagerInterface : public Observer
{

public:

    using unique_type = Observer::unique_type;

    virtual void boradcast(packet::Packet& packet) = 0;

    virtual void detach(unique_type obs) = 0;

    virtual Json::Value toJson() const override final
    {
        assert(0);
        return Json::Value{};
    };

    virtual const std::string_view& getUniqueName() const override final
    {
        assert(0);
        return NAME_NULL;
    }

};
}

#endif //SDL2_TETRIS_SERVER_MANAGERINTERFACE_H

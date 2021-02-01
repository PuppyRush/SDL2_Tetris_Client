//
// Created by chaed on 19. 2. 16.
//

#ifndef GAMEINTERFACE_OBSERVER_H
#define GAMEINTERFACE_OBSERVER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Type.h"
#include "Packet.h"
#include "Object.h"

namespace game_interface {

//pre-declarcation
class Observer : public Object
{
public:

    using unique_type = Object::unique_type;

    Observer() = default;

    virtual ~Observer() = default;

    virtual void updateObserver(const packet::Packet&) = 0;

    virtual const std::string_view& getUniqueName() const = 0;

    virtual Json::Value toJson() const = 0;

};

}

#endif //SDL2EASYGUI_SUBJECT_H

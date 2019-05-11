//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_SUBJECT_H
#define TETRIS_FIGURE_CLASS_SUBJECT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "GameInterface/include/Type.h"
#include "GameInterface/include/Packet.h"
#include "GameInterface/include/Object.h"

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

#endif //TETRIS_FIGURE_CLASS_SUBJECT_H

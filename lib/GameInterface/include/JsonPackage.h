//
// Created by chaed on 19. 4. 17.
//

#ifndef UICLASSEXAMPLE_JSONPACKAGE_H
#define UICLASSEXAMPLE_JSONPACKAGE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <json/json.h>

namespace game_interface {

class JsonPackage
{
public:
    virtual Json::Value toJson() const = 0;

    virtual void fromJson(const Json::Value& json) = 0;

    virtual const std::string_view& getUniqueName() const = 0;
};
}

#endif //UICLASSEXAMPLE_JSONPACKAGE_H



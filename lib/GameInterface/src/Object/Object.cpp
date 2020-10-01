#include <ctime>

#include "Object.h"

using namespace game_interface;

Object::Object()
        : m_unique(atomic::Atomic<Object>::getInstance().newUnique()), m_maketime(std::time(nullptr))
{
}

Json::Value Object::toJson() const
{
    Json::Value json;
    json["unique"] = static_cast<Json::Value::UInt64>(getUnique());
    json["maketime"] = static_cast<Json::Value::UInt64>(getMaketime());

    return json;
}

void Object::fromJson(const Json::Value& json)
{
    setUnique(json["unique"].asUInt64());
    setMaketime(json["maketime"].asUInt64());
}
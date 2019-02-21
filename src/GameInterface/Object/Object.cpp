#include "Object.h"

using namespace game_interface;

Object::Object()
    :m_unique(Atomic::newUnique())
{
}

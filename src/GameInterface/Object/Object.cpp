#include <ctime>

#include "Object.h"

using namespace game_interface;

Object::Object()
    :m_unique(Atomic::newUnique()), m_maketime(std::time(nullptr))
{
}

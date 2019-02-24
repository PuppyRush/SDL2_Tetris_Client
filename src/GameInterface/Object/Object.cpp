#include <cassert>
#include <GameInterface/Constant.h>

#include "Object.h"

using namespace game_interface;

Object::Object()
    :m_unique(Atomic::newUnique())
{
    //full unique
    assert(m_unique != NULL_ID);
}

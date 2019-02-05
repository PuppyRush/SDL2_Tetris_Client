#include "Object.h"

Object::Object()
    :m_unique(Atomic::newUnique())
{
}

#include "Object.h"
#include "Atomic.h"

SDL_TETRIS

Object::Object()
    :m_unique(Atomic::newUnique())
{
}

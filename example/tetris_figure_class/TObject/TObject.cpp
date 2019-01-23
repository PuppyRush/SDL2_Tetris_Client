#include "TObject.h"
#include "TAtomic.h"

SDL_TETRIS

TObject::TObject()
    :m_unique(TAtomic::newUnique())
{
}

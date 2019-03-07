//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"

using namespace sdleasygui;

ListBox::ListBox(ListBoxBuilder &bld)
    :Border(bld)
{
    bld.kind(ControllKind::ListBox);
}



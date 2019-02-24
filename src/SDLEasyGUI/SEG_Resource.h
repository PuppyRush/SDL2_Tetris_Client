//
// Created by chaed on 19. 2. 5.
//

#ifndef SDLEASYGUIDE_RESOURCE_H
#define SDLEASYGUIDE_RESOURCE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SEG_Type.h"

namespace sdleasygui {

//dont use resource id as 0x0000 (NULL)
enum resource : t_res {

    BTN_OK = 0x0010,
    BTN_NO,
    BTN_CANCEL,

    SEG_RESROUCE_END = 0x3000
};

}

#endif //TETRIS_FIGURE_CLASS_RESOURCE_H

//
// Created by chaed on 19. 2. 5.
//

#ifndef SDLEASYGUIDE_RESOURCE_H
#define SDLEASYGUIDE_RESOURCE_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SEG_Type.h"

namespace seg {

//dont use resource id as 0x0000 (NULL)
enum resource : t_id
{

    NONE = 0x0010,
    BTN_OK,
    BTN_YES,
    BTN_NO,
    BTN_CLOSE,
    BTN_CANCEL,

    MESSAGEDIALOG_MSG,

    MAIN_DISPLAY,
    MESSAGE_DIALOG,
    INPUT_DIALOG,

    SEG_RESROUCE_END = 0x3000
};

}

#endif //TETRIS_FIGURE_CLASS_RESOURCE_H

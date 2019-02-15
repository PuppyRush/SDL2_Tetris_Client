//
// Created by chaed on 18. 11. 24.
//

#ifndef SDLEASYGUIDE_TPROPERTY_H
#define SDLEASYGUIDE_TPROPERTY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

const t_size WINDOW_HEIGHT = 900;
const t_size WINDOW_WIDTH = 1000;


enum class TControllKind : t_type
{
    StaticLabel,
    EditLabel,
    Button,
    RadioButton,
    Border
};

enum class TDisplayMode : t_type
{
    Modal,
    Modaless
};


enum class TLocalMode : t_type
{
    Local,
    Online,
    All
};

enum class TColorCode : t_type
{
    red = 0,
    blue,
    orange,
    yellow,
    purple,
    green,
    black,
    white,
    silver,
    none,
    Begin = red,
    End = green
};

enum EventType
{
    SDL_EASYGUI_EVENT_START =  0x9000,
    SDL_DRAW_DISPLAY ,
    SDL_CLICKED_CONTROLLER,
};

typedef struct UserEvent {
    static  t_eventType SDLEASYGUI_EVENT;
}UserEvent;


#endif //TERIS_FIGURE_CLASS_TPROPERTY_H

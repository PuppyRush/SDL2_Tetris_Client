
#include "SDLEasyGUI/Windows/DisplayController.h"

#include "Tetris/Common/Resource.h"
#include "Tetris/TDisplay/TGameLocalDisplay.h"
#include "Tetris/TDisplay/TGameOnlineDisplay.h"
#include "Tetris/TDisplay/TMainLocalDisplay.h"

#define SDL_DEBUG_EVENTS

SDL_TETRIS

void init()
{

    //background
    //TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
    auto ev = SDL_RegisterEvents(100);

}

int main()
{
    init();

    auto ctl = DisplayController::getInstance();
    auto result = ctl->modal(make_shared<TGameOnlineDisplay>());


}

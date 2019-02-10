
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/SEG_Initiator.h"
#include "SDLEasyGUI/SEG_Quit.h"

#include "Tetris/Common/Resource.h"
#include "Tetris/TDisplay/TSingleGameDisplay.h"
#include "Tetris/TDisplay/TMultiGameRoomDisplay.h"
#include "Tetris/TDisplay/TMainLocalDisplay.h"
#include "Tetris/TDisplay/TMainOnlineDisplay.h"

#define SDL_DEBUG_EVENTS

SDL_TETRIS

void init()
{

    SDLEasyGUI_Init();

    //background
    //TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
    auto ev = SDL_RegisterEvents(100);

}

int main() {
    init();

    auto ctl = DisplayController::getInstance();
    auto result = ctl->modal(make_shared<TMainOnlineDisplay>());
    ctl->run();

    SDLEasyGUI_Quit();
}
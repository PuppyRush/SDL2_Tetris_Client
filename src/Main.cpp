
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/SEG_Initiator.h"
#include "SDLEasyGUI/SEG_Quit.h"

#include "Tetris/Common/TResource.h"
#include "Tetris/TDisplay/Game/TSingleGameDisplay.h"
#include "Tetris/TDisplay/Game/TMultiGameRoomDisplay.h"
#include "Tetris/TDisplay/Main/TMainLocalDisplay.h"
#include "Tetris/TDisplay/Main/TMainOnlineDisplay.h"

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



    auto maindlg = make_shared<TMainOnlineDisplay>();
    maindlg->modal();

    SDLEasyGUI_Quit();
}
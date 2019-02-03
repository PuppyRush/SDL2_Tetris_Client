
#include "SDLEasyGUI/Windows/DisplayController.h"

#include "Tetris/TDisplay/TGameLocalDisplay.h"
#include "Tetris/TMain/TMainLocalDisplay.h"

SDL_TETRIS

void init()
{

    //background
    TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
    SDL_RegisterEvents(TETRIS_EVENT_FIGURETIMER);
}

int main()
{
    init();

    DisplayController::getInstance()->setDisplay(TDisplay::Main);
    DisplayController::getInstance()->operateGame();
}

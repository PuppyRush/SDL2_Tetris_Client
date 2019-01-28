
#include "TDisplay/TGameLocalDisplay.h"
#include "Interface/GUI/DisplayController.h"
#include "TMain/TMainLocalDisplay.h"

SDL_TETRIS

void init()
{

    //background
    TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
    SDL_RegisterEvents(SDL_DRAWDISPLAY);
}

int main()
{
    init();

    DisplayController::getInstance()->setDisplay(TDisplay::Main);
    DisplayController::getInstance()->operateGame();
}

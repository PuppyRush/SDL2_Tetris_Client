
#include "TGame/TGameLocalDisplay.h"
#include "TDisplay/TDisplayController.h"
#include "TMain/TMainLocalDisplay.h"

SDL_TETRIS

void init()
{

    //background
    TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
    SDL_RegisterEvents(SDL_DRAWDISPLAY);
}

int main(int argc, char** args)
{
    init();

    TDisplayController::getInstance()->setDisplay(TDisplay::Main);
    TDisplayController::getInstance()->operateGame();

	return 0;
}

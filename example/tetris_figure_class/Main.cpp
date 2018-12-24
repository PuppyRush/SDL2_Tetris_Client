
#include "TGame/TGameLocalDisplay.h"
#include "TDisplay/TDisplayController.h"
#include "TMain/TMainLocalDisplay.h"

SDL_TETRIS

int main()
{

    TMainLocalDisplay::getInstance()->setBackgroundImgPath("resources/background.jpg");

    TDisplayController::getInstance()->setDisplay(TDisplay::Game);
    TDisplayController::getInstance()->operateGame();
}

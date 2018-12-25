
#include "TGame/TGameLocalDisplay.h"
#include "TDisplay/TDisplayController.h"
#include "TMain/TMainLocalDisplay.h"

SDL_TETRIS

int main()
{

    TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");



    TDisplayController::getInstance()->setDisplay(TDisplay::Main);

    TDisplayController::getInstance()->operateGame();
}


#include "TGame/TGameLocalDisplay.h"
#include "TDisplay/TDisplayController.h"
#include "TMain/TMainLocalDisplay.h"

SDL_TETRIS

int main()
{

    TMainLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    TMenuBuilder bld;
    bld.name("START")->
    point({WINDOW_WIDTH/2-50, WINDOW_HEIGHT/3})->
    font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColor::white})->
    width(100)->
    height(50)->
    display(TDisplay::Game)->
    add();

    bld.name("EXIT")->
    point({WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2})->
    font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColor::white})->
    width(100)->
    height(50)->
    display(TDisplay::Exit)->
    add();

    TMainLocalDisplay::getInstance()->addMenu(bld);

    TDisplayController::getInstance()->setDisplay(TDisplay::Main);

    TDisplayController::getInstance()->operateGame();
}

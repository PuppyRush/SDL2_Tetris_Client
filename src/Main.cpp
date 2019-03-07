
#include <condition_variable>
#include <mutex>
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "SDLEasyGUI/SEG_Initiator.h"
#include "SDLEasyGUI/SEG_Quit.h"

#include "Tetris/Common/TResource.h"
#include "Tetris/TDisplay/Game/TSingleGameDisplay.h"
#include "Tetris/TDisplay/Game/TMultiGameRoomDisplay.h"
#include "Tetris/TDisplay/Main/TLocalMainDisplay.h"
#include "Tetris/TDisplay/Main/TMultiMainDisplay.h"
#include "GameInterface/Online/PacketQueue.h"

#define SDL_DEBUG_EVENTS

SDL_TETRIS

void init()
{

    game_interface::PacketQueue::getInstance().setServer(false);
    sdleasygui::SDLEasyGUI_Init();

    //background
    //TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");

    //Registry Event
//    SDL_RegisterEvents(SEG_DRAW_DISPLAY);

}

int main() {
    init();


    sdleasygui::t_res res;
    do{
        auto maindlg = std::make_shared<TMultiMainDisplay>();
        res = maindlg->modal();
    }while(res != game_interface::toUType(resource::MAIN_EXIT));

    sdleasygui::SDLEasyGUI_Quit();
}

#include <condition_variable>
#include <mutex>

#include "SDL2EasyGUI/src/Windows/DisplayController.h"
#include "SDL2EasyGUI/src/SEG_Initiator.h"
#include "SDL2EasyGUI/src/SEG_Quit.h"

#include "Common/TResource.h"
#include "TDisplay/Game/TSingleGameDisplay.h"
#include "TDisplay/Game/TMultiGameRoomDisplay.h"
#include "TDisplay/Main/TLocalMainDisplay.h"
#include "TDisplay/Main/TMultiMainDisplay.h"
#include "GameInterface/src/Online/PacketQueue.h"

#define SDL_DEBUG_EVENTS

SDL_TETRIS

void init()
{
    sdleasygui::SDLEasyGUI_Init();

    game_interface::PacketQueue::getInstance().setServer(false);
    game_interface::PacketQueue::getInstance().initialize();

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
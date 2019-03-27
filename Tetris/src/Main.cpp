
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
#include "GameInterface/src/Quit.h"

#define SDL_DEBUG_EVENTS

SDL_TETRIS

void init()
{
    sdleasygui::SDLEasyGUI_Init();

    game_interface::PacketQueue::getInstance().setServer(false);
    game_interface::PacketQueue::getInstance().initialize();

    //background
    //TGameLocalDisplay::getInstance()->setBackgroundImgPath("../resources/images/background.png");


}

int main() {
    init();

    sdleasygui::t_res res;
    auto maindlg = std::make_shared<TMultiMainDisplay>();

    maindlg->modaless(maindlg);

    if(res != game_interface::toUType(resource::MAIN_EXIT))
    {

    }



    while(true);

    game_interface::GameInterface_Quit();
    sdleasygui::SDLEasyGUI_Quit();
}
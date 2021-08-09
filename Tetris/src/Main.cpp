
#include <condition_variable>
#include <mutex>
#include <thread>

#include "SDL2EasyGUI/include/DisplayController.h"
#include "SDL2EasyGUI/include/MessageDialog.h"
#include "SDL2EasyGUI/include/SEG_Initiator.h"
#include "SDL2EasyGUI/include/SEG_Quit.h"

#include "GameInterface/include/Initiator.h"
#include "GameInterface/include/PacketQueue.h"
#include "GameInterface/include/Quit.h"

#include "TResource.h"

#include "TDisplay/Game/TSingleGameDisplay.h"
#include "TDisplay/Game/TMultiGameRoomDisplay.h"
#include "TDisplay/Main/TLocalMainDisplay.h"
#include "TDisplay/Main/TMultiMainDisplay.h"
#include "TDisplay/Waiting/TCreateGameroomDisplay.h"
#include "TDisplay/Waiting/TWaitingRoomDisplay.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;


#undef main

void init()
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    game_interface::GameInterface_Init(false);
    seg::SDLEasyGUI_Init();
	seg::SetMaindisplay<TMultiMainDisplay>();

    TPlayer::getInstance()->setOrder(0);
    TPlayer::getInstance()->setMaster(true);
	
}

int main(int argc, char **argv)
{
    init();
	seg::Start();
		
    game_interface::GameInterface_Quit();
    seg::SDLEasyGUI_Quit();

	return 0;
}


#define main

#include <condition_variable>
#include <mutex>

#include "SDL2EasyGUI/include/DisplayController.h"
#include "SDL2EasyGUI/src/Display/MessageDialog.h"
#include "SDL2EasyGUI/include/SEG_Initiator.h"
#include "SDL2EasyGUI/include/SEG_Quit.h"

#include "GameInterface/src/Online/PacketQueue.h"
#include "GameInterface/include/Quit.h"

#include "Common/TResource.h"

#include "TDisplay/Game/TSingleGameDisplay.h"
#include "TDisplay/Game/TMultiGameRoomDisplay.h"
#include "TDisplay/Main/TLocalMainDisplay.h"
#include "TDisplay/Main/TMultiMainDisplay.h"
#include "TDisplay/Waiting/TCreateGameroomDisplay.h"
#include "TDisplay/Waiting/TWaitingRoomDisplay.h"

SDL_TETRIS

using namespace std;
using namespace game_interface;

void init()
{
    sdleasygui::SDLEasyGUI_Init();

    game_interface::PacketQueue::getInstance().setServer(false);
    game_interface::PacketQueue::getInstance().run();

}

int main() {

    init();

    sdleasygui::t_res res;
    shared_ptr<TDisplayInterface> maindlg;

    auto mainDisplay = sdleasygui::make_display<TMultiMainDisplay>(resource::MAIN_MULTI_DISPLAY);
    mainDisplay->setWindowHeight(900);
    mainDisplay->setWindowWidth(800);
    mainDisplay->setWindowTitle("TetrisGame");
    mainDisplay->setBackgroundImgPath("../resources/images/background.png");

    auto optionDisplay = sdleasygui::make_display<TOptionDisplay>(resource::OPTION_DISPLAY);
    optionDisplay->setWindowHeight(900);
    optionDisplay->setWindowWidth(800);
    optionDisplay->setWindowTitle("Option");

    auto enterServerDisplay = sdleasygui::make_display<TEnterServerDisplay>(resource::ENTERSERVER_DISPLAY);
    enterServerDisplay->setWindowHeight(300);
    enterServerDisplay->setWindowWidth(300);
    enterServerDisplay->setWindowTitle("Input Your Nickname");

    auto waitingRoomDisplay = sdleasygui::make_display<TWaitingRoomDisplay>(resource::WAITINGROOM_DISPLAY);
    waitingRoomDisplay->setWindowTitle("Hello Tetris World!");

    bool go = true;
    maindlg = mainDisplay;
    while(go)
    {
        maindlg->modal(maindlg);
        if(maindlg->compareDisplay(resource::MAIN_MULTI_DISPLAY))
        {
            switch(maindlg->getResult())
            {
                case toUType(resource::MAIN_EXIT):
                    go = false;
                    break;
                case toUType(resource::MAIN_OPTION_BUTTON): {

                    optionDisplay->modal(optionDisplay);
                    break;
                }
                case toUType(resource::MAIN_MULTI_GAME_START_BUTTON): {

                    while(true) {
                        enterServerDisplay->modal(enterServerDisplay);

                        if (enterServerDisplay->getResult() == toUType(resource::ENTERSERVER_OK)) {
                            auto& player = TPlayer::getInstance();

                            if (player->connectServer()) {
                                game_interface::PacketQueue::getInstance().attach(player);
                                break;
                            }
                            else
                            {
                                sdleasygui::MessageDialog dlg{"Cannot fail to connect server.",
                                                              sdleasygui::MessageDialogKind::error};
                                dlg.alert();
                            }
                        }
                        else
                            break;
                    }
                    maindlg = waitingRoomDisplay;
                    break;
                }

                default:
                    assert(0);
            }
        }
        else if(maindlg->compareDisplay(resource::WAITINGROOM_DISPLAY)) {

            if(!TPlayer::getInstance()->getClientController().isConnection())
            {
                maindlg = mainDisplay;
                break;
            }

            switch(maindlg->getResult()) {
                case toUType(resource::WAITINGROOM_CREATE):


                    break;

            }

        }


    }



    game_interface::GameInterface_Quit();
    sdleasygui::SDLEasyGUI_Quit();
}
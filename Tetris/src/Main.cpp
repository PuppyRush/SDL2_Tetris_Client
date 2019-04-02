
#include <condition_variable>
#include <mutex>

#include "SDL2EasyGUI/src/Windows/DisplayController.h"
#include "SDL2EasyGUI/src/Display/MessageDialog.h"
#include "SDL2EasyGUI/src/SEG_Initiator.h"
#include "SDL2EasyGUI/src/SEG_Quit.h"

#include "Common/TResource.h"
#include "TDisplay/Game/TSingleGameDisplay.h"
#include "TDisplay/Game/TMultiGameRoomDisplay.h"
#include "TDisplay/Main/TLocalMainDisplay.h"
#include "TDisplay/Main/TMultiMainDisplay.h"
#include "TDisplay/Waiting/TWaitingRoomDisplay.h"
#include "GameInterface/src/Online/PacketQueue.h"
#include "GameInterface/src/Quit.h"

SDL_TETRIS

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
    auto maindlg = std::make_shared<TMultiMainDisplay>();
    maindlg->setWindowHeight(900);
    maindlg->setWindowWidth(800);
    maindlg->setWindowTitle("TetrisGame");
    maindlg->setBackgroundImgPath("../resources/images/background.png");

    auto optionDisplay = std::make_shared<TOptionDisplay>();
    optionDisplay->setWindowHeight(900);
    optionDisplay->setWindowWidth(800);
    optionDisplay->setWindowTitle("Option");

    auto enterServerDisplay = std::make_shared<TEnterServerDisplay>();
    enterServerDisplay->setWindowHeight(300);
    enterServerDisplay->setWindowWidth(300);
    enterServerDisplay->setWindowTitle("Input Your Nickname");

    bool go = true;
    while(go)
    {
        maindlg->modal(maindlg);
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
                        auto player = TPlayer::getInstance();

                        if (player->connectServer()) {
                            game_interface::PacketQueue::getInstance().attach(player);
                            go = false;
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
                break;
            }
            default:
                assert(0);
        }
    }

    if(TPlayer::getInstance()->getClientController().isConnection())
    {
        auto dlg = std::make_shared<TWaitingRoomDisplay>();
        dlg->setWindowTitle("Hello Tetris World!");
        dlg->modal(dlg);
    }

    game_interface::GameInterface_Quit();
    sdleasygui::SDLEasyGUI_Quit();
}

#include <condition_variable>
#include <mutex>

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

void init()
{
    game_interface::GameInterface_Init(false);
    sdleasygui::SDLEasyGUI_Init();

    TPlayer::getInstance()->setOrder(0);
    TPlayer::getInstance()->setMaster(true);
}

int main()
{

    init();
    sdleasygui::t_res res;

    auto mainDisplay = sdleasygui::make_display<TMultiMainDisplay>(resource::MAIN_MULTI_DISPLAY);
    auto optionDisplay = sdleasygui::make_display<TOptionDisplay>(resource::OPTION_DISPLAY);
    auto enterServerDisplay = sdleasygui::make_display<TEnterServerDisplay>(resource::ENTERSERVER_DISPLAY);
    auto waitingRoomDisplay = sdleasygui::make_display<TWaitingRoomDisplay>(resource::WAITINGROOM_DISPLAY);

    bool go = true;
    shared_ptr<TDisplayInterface> maindlg = mainDisplay;
    while (go) {
        maindlg->modal(maindlg);
        if (maindlg->compareDisplay(resource::MAIN_MULTI_DISPLAY)) {
            switch (maindlg->getResult()) {
                case toUType(resource::MAIN_EXIT):
                    go = false;
                    break;
                case toUType(resource::MAIN_OPTION_BUTTON): {

                    optionDisplay->modal(optionDisplay);
                    break;
                }
                case toUType(resource::MAIN_MULTI_GAME_START_BUTTON): {

                    while (true) {
                        enterServerDisplay->modal(enterServerDisplay);

                        if (enterServerDisplay->m_valid) {
                            auto& player = TPlayer::getInstance();

                            if (player->connectServer()) {
                                game_interface::PacketQueue::getInstance().attach(player);
                                maindlg = waitingRoomDisplay;
                                break;
                            } else {
                                sdleasygui::MessageDialog dlg{"Cannot fail to connect server.",
                                                              sdleasygui::MessageDialogKind::error};
                                dlg.alert();
                            }
                        } else if (enterServerDisplay->getResult() == sdleasygui::toUType(sdleasygui::BTN_CANCEL)) {
                            break;
                        }
                    }

                    break;
                }

                default:
                    assert(0);
            }
        } else if (maindlg->compareDisplay(resource::WAITINGROOM_DISPLAY)) {

            if (!TPlayer::getInstance()->getClientController().isConnection()) {
                maindlg = mainDisplay;
                break;
            }

            switch (maindlg->getResult()) {
                case toUType(resource::WAITINGROOM_CREATE):

                    break;

            }

        }

    }

    game_interface::GameInterface_Quit();
    sdleasygui::SDLEasyGUI_Quit();
}
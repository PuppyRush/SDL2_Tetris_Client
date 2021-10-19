//
// Created by chaed on 19. 2. 14.
//

#include "SDL2EasyGUI/include/MessageDialog.h"
#include "SDL2EasyGUI/include/EditLabel.h"
#include "SDL2EasyGUI/include/DisplayController.h"
#include "GameInterface/include/PacketQueue.h"
#include "../../TObject/TPlayer.h"
#include "TEnterServerDisplay.h"
#include "TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace seg;

TEnterServerDisplay::TEnterServerDisplay()
{
}

void TEnterServerDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::ENTERSERVER_ENTER), &TEnterServerDisplay::onClickedEnterServer, this);
    SEG_LBUTTONCLICK(seg::toUType(resource::ENTERSERVER_BACK), &TEnterServerDisplay::onClickedBack, this);
}

void TEnterServerDisplay::onInitialize()
{

    setWindowHeight(300);
    setWindowWidth(300);
    setWindowTitle("Input Your Nickname");
    setBackgroundColor(SEG_Color{ ColorCode::lightgray });

    seg::t_size begin_y = getWindowHeight() / 3;
    {
        EditLabelBuilder bld(getSEGWindow(), {getWindowWidth() / 2 - 120, begin_y}, "Player");
        bld.id(seg::toUType(resource::ENTERSERVER_ID))->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                fontColor(ColorCode::black)->
                width(240)->
                height(50)->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }

    begin_y += 80;
    {
        ButtonBuilder bld(getSEGWindow(), {getWindowWidth() / 2 - 120, begin_y}, "ENTER");
        bld.id(seg::toUType(resource::ENTERSERVER_ENTER))->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(100)->
                height(50)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }

    {
        ButtonBuilder bld(getSEGWindow(), {getWindowWidth() / 2, begin_y}, "BACK");
        bld.id(seg::toUType(resource::ENTERSERVER_BACK))->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(100)->
                height(50)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

        addControl(bld.build());
    }
    
    setWindowResizable(false);
    TDisplayInterface::onInitialize();
}

void TEnterServerDisplay::onClickedEnterServer(const void* click)
{
    auto& player = TPlayer::getInstance();
    const auto& idLabel = getControl<EditLabel>(resource::ENTERSERVER_ID);

    if (idLabel->getControlText().size() < 5) {
        assert(idLabel != nullptr);

        auto message = DisplayController::modal_open<MessageDialog>("Enter Your ID at least 5 characters", seg::MessageDialogKind::error);
        message->modal();

        m_valid = false;
    }
    else{
        m_valid = true;
        TDisplayInterface::onOk();
    }

}

void TEnterServerDisplay::onClickedBack(const void* click)
{
    TDisplayInterface::onButtonClick(click);
    onClose();
}
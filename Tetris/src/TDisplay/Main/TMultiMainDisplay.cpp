
//
// Created by chaed on 18. 12. 18.
//

#include "SDL2EasyGUI/include/Button.h"
#include "SDL2EasyGUI/include/ComboBox.h"
#include "SDL2EasyGUI/include/ListBox.h"
#include "SDL2EasyGUI/include/RadioButton.h"
#include "SDL2EasyGUI/include/CheckBox.h"
#include "SDL2EasyGUI/include/DisplayController.h"
#include "SDL2EasyGUI/include/SEG_Constant.h"

#include "SDL2EasyGUI/src/Decorator/ScrollbarDecorator.h"
#include "SDL2EasyGUI/src/Decorator/BorderDecorator.h"

#include "../Waiting/TWaitingRoomDisplay.h"
#include "TMultiMainDisplay.h"
#include "../TOptionDisplay.h"
#include "TResource.h"

SDL_TETRIS
using namespace game_interface;
using namespace seg;

TMultiMainDisplay::TMultiMainDisplay()     
{
}

void TMultiMainDisplay::registerEvent()
{
    SEG_LBUTTONCLICK(seg::toUType(resource::MAIN_MULTI_GAME_START_BUTTON),
                     &TMultiMainDisplay::onClickedEnterServer,
                     this);
    SEG_LBUTTONCLICK(seg::toUType(resource::MAIN_OPTION_BUTTON),
                     &TMultiMainDisplay::onClickedOption,
                     this);

    SEG_LBUTTONCLICK(seg::toUType(resource::MAIN_LIST_ADD),
        &TMultiMainDisplay::onClickedAddList,
        this);
    SEG_LBUTTONCLICK(seg::toUType(resource::MAIN_LIST_REMOVE),
        &TMultiMainDisplay::onClickedRemoveList,
        this);

    SEG_LBUTTONCLICK(seg::toUType(resource::MAIN_EXIT), &TMultiMainDisplay::onClickedBack, this);
}

void TMultiMainDisplay::onInitialize()
{

    seg::t_size begin_x = WINDOW_WIDTH / 2 - 220;
    seg::t_size begin_y = WINDOW_HEIGHT / 3;
    {
        ButtonBuilder bld(getSEGWindow(), {begin_x, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                backgroundColor(ColorCode::white)->
                id(game_interface::toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
                width(240)->
                height(50)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                borderColor(ColorCode::silver)->
                borderThick(4)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getSEGWindow(), {WINDOW_WIDTH / 2 - 150, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_OPTION_BUTTON))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getSEGWindow(), {WINDOW_WIDTH / 2 - 150, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_EXIT))->
                backgroundColor(ColorCode::white)->
                borderBoundaryType(BorderBoundaryType::roundedAngle)->
                width(100)->
                height(50)->
                enabled(true);

        addControl(bld.build());
    }
    begin_y + 50;
    begin_x -= 100;
    {
        ButtonBuilder bld(getSEGWindow(), { begin_x , begin_y }, "Add");
        bld.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black })->
            id(game_interface::toUType(resource::MAIN_LIST_ADD))->
            backgroundColor(ColorCode::white)->
            borderBoundaryType(BorderBoundaryType::roundedAngle)->
            width(100)->
            height(50)->
            enabled(true);

        addControl(bld.build());
    }

    begin_y += 50;
    {
        ButtonBuilder bld(getSEGWindow(), { begin_x , begin_y }, "Remove");
        bld.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black })->
            id(game_interface::toUType(resource::MAIN_LIST_REMOVE))->
            backgroundColor(ColorCode::white)->
            borderBoundaryType(BorderBoundaryType::roundedAngle)->
            width(100)->
            height(50)->
            enabled(true);

        addControl(bld.build());
    }

    //begin_y += 80;
    //{
    //    ComboBoxBuilder bld(getSEGWindow(), {WINDOW_WIDTH / 2, begin_y}, "DoitNow");
    //    bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
    //            id(game_interface::toUType(resource::MAIN_TEST_TEXT_COMBO))->
    //            backgroundColor(ColorCode::white)->
    //            borderBoundaryType(BorderBoundaryType::roundedAngle)->
    //            width(120)->
    //            height(30)->
    //            enabled(true);

    //    BoxItemBuilder bibld1(getSEGWindow(), "one");
    //    bibld1.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black })->
    //        backgroundColor(ColorCode::white);
    //    bld.addItem(bibld1);
    //    bld.addItem("two");
    //    bld.addItem("three" );
    //    bld.addItem("four4" );
    //    addControl(bld.build());

    //    ComboBox* ctl = getControl<ComboBox>(resource::MAIN_TEST_TEXT_COMBO);
    //    ctl->addItem("five");
    //    ctl->addItem("six");
    //    ctl->addItem("seven");
    //}

    begin_y += 80;
    {
        CheckBoxBuilder bld(getSEGWindow(), {WINDOW_WIDTH / 2, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_TEST_CHECKBOX))->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::lightgray)->
                borderBoundaryType(BorderBoundaryType::angle)->
                borderThick(3)->

                enabled(true);

        addControl(bld.build());
    }

    begin_y += 30;
    {
        RadioButtonBuilder bld(getSEGWindow(), {WINDOW_WIDTH / 2, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_TEST_RADIOBUTTON))->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::lightgray)->
                borderBoundaryType(BorderBoundaryType::angle)->
                borderAngle(5)->
                borderThick(3)->
                grouping(1)->
                enabled(true);

        addControl(bld.build());
    }

    begin_x += 50;
    {
        RadioButtonBuilder bld(getSEGWindow(), {begin_x, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_TEST_RADIOBUTTON2))->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::lightgray)->
                borderLineType(BorderBoundaryLineType::round)->
                borderThick(3)->
                grouping(1)->
                multiselected(false)->
                enabled(true);

        addControl(bld.build());
    }

    begin_x += 50;
    {
        RadioButtonBuilder bld(getSEGWindow(), {begin_x, begin_y}, "");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
                id(game_interface::toUType(resource::MAIN_TEST_RADIOBUTTON3))->
                backgroundColor(ColorCode::white)->
                borderColor(ColorCode::lightgray)->
                borderLineType(BorderBoundaryLineType::round)->
                borderThick(3)->
                grouping(1)->
                enabled(true);

        auto ctl = bld.build();
        addControl(ctl);
    }

    {
        ListBoxBuilder bld(getSEGWindow(), { 30, 300 }, "first");
        bld.font({ "../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black })->
            id(game_interface::toUType(resource::MAIN_TEST_LISTBOX))->
            height(500)->width(100)->
            backgroundColor(ColorCode::white)->
            borderColor(ColorCode::lightgray)->
            borderBoundaryType(BorderBoundaryType::angle)->
            borderAngle(3)->
            borderThick(2)->
            grouping(1)->
            enabled(true);

        bld.addItem("aaabbb")->
        addItem("aaabb1111b")->
        addItem("aaabbb22222")->
        addItem("abaabab333");


        addControl(bld.build());
    }

    setWindowHeight(900);
    setWindowWidth(800);
    setWindowTitle("TetrisGame");
    setBackgroundImgPath("../resources/images/background.png");

    TMainDisplay::onInitialize();
}

void TMultiMainDisplay::onDraw()
{
    TMainDisplay::onDraw();
}

void TMultiMainDisplay::onClickedAddList(const void* click)
{
    static int i = 0;
    auto list = getControl<ListBox>(resource::MAIN_TEST_LISTBOX);
    std::string str;
    str += "add";
    char c[10];
    itoa(i++, c, 10);
    str.append(c);
    list->addItem(str);
}

void TMultiMainDisplay::onClickedRemoveList(const void* click)
{
    auto list = getControl<ListBox>(resource::MAIN_TEST_LISTBOX);
    list->removeItem(0);

}

void TMultiMainDisplay::onClickedOption(const void* click)
{
    auto dp = DisplayController::modal_open<TOptionDisplay>();
    dp->modal();

    TMainDisplay::onButtonClick(click);
}

#include "../../TObject/TPlayer.h"
#include "GameInterface/include/PacketQueue.h"
#include "SDL2EasyGUI/include/MessageDialog.h"

void TMultiMainDisplay::onClickedEnterServer(const void* click)
{
    auto dp = DisplayController::modal_open<TEnterServerDisplay>();
    dp->modal();

  	auto& player = TPlayer::getInstance();

	if (player->connectServer()) {
		game_interface::PacketQueue::getInstance().attach(player);

        auto waitingRoomDisplay = DisplayController::modal_open<TWaitingRoomDisplay>();
        waitingRoomDisplay->modal();
	}
	else {
		seg::MessageDialog dlg{ "Cannot fail to connect server.",
								seg::MessageDialogKind::error };
		dlg.alert();
	}

    TMainDisplay::onButtonClick(click);
}

void TMultiMainDisplay::onClickedBack(const void* click)
{
    TMainDisplay::onOk();
}

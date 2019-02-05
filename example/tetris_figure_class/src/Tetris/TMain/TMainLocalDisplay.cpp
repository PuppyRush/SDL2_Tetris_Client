//
// Created by chaed on 18. 12. 18.
//

#include "TMainLocalDisplay.h"
#include "SDLEasyGUI/Controller/Button.h"

SDL_TETRIS

TMainLocalDisplay::TMainLocalDisplay()
    :TMainDisplay()
{}

std::shared_ptr<TMainDisplay> TMainLocalDisplay::getInstance()
{
    //boost::serialization::singleton<TMainLocalDisplay>::get_mutable_instance();
    static std::shared_ptr<TMainDisplay> inst = std::shared_ptr<TMainLocalDisplay>(new TMainLocalDisplay{});
    return inst;
}

void TMainLocalDisplay::onPreInitialize() {
    setBackgroundImgPath("../resources/images/background.png");

    t_size begin_y = WINDOW_HEIGHT/3;

    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 100, begin_y}, "PLAY ALONE");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(200)->
            height(50)->
            enabled(true)->
            display(TDisplay::SingleGame);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(240)->
            height(50)->
            enabled(true)->
            display(TDisplay::OnlineGame);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/2-50, begin_y}, "OPTION");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true)->
            display(TDisplay::Option);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(),{WINDOW_WIDTH/2-50, begin_y}, "EXIT");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true)->
            display(TDisplay::Exit);

        addControll(Button::getInstance(bld));
    }
}


bool TMainLocalDisplay::onClickedEnterServer()
{}

bool TMainLocalDisplay::onClickedStartLocalGame()
{}

bool TMainLocalDisplay::onClickedBack(const TDisplay display)
{
    setDisplay(display);
}

void TMainLocalDisplay::_timer()
{

}

void TMainLocalDisplay::_event(const SDL_Event* event) {

    DisplayInterface::_event(event);
}

void TMainLocalDisplay::onDraw()
{

}

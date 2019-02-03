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

void TMainLocalDisplay::_preInitialize() {
    setBackgroundImgPath("../resources/images/background.png");

    constexpr const t_size begin_y = WINDOW_HEIGHT/3;

    {
        ControllBuilder bld(getWindow().get(), {WINDOW_WIDTH / 2 - 50, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true)->
            display(TDisplay::Game);

        addControll(Button::getInstance(bld));
    }
    {
        ControllBuilder bld(getWindow().get(), {WINDOW_WIDTH/2-50, begin_y+80}, "OPTION");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true)->
            display(TDisplay::Option);

        addControll(Button::getInstance(bld));
    }
    {
        ControllBuilder bld(getWindow().get(),{WINDOW_WIDTH/2-50, begin_y+160}, "EXIT");
            bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true)->
            display(TDisplay::Exit);

        addControll(Button::getInstance(bld));
    }
}


bool TMainLocalDisplay::clickedEnterServer()
{}

bool TMainLocalDisplay::clickedStartLocalGame()
{}

bool TMainLocalDisplay::clickedBack(const TDisplay display)
{
    setDisplay(display);
}

void TMainLocalDisplay::_timer()
{

}

void TMainLocalDisplay::_event(const SDL_Event* event) {

    DisplayInterface::_event(event);
}

void TMainLocalDisplay::_draw()
{

    //setStopDraw(true);
}

//
// Created by chaed on 18. 12. 18.
//

#include "TMainLocalDisplay.h"

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

    switch (event->type) {
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_KEYDOWN:
            break;
        case SDL_MOUSEBUTTONDOWN: {
            const TPoint point(event->button.x, event->button.y);
            if (clickedMenuEvent(point))
            {
                setRun(false);
                break;
            }

            break;
        }
        default:;
    }
}

void TMainLocalDisplay::_draw()
{
    auto renderer = getRenderer().get();
    auto window = getWindow().get();
    auto event = getSDLEvent().get();

}

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


void TMainLocalDisplay::_event()
{

}

void TMainLocalDisplay::_draw()
{
    using namespace std;

    auto renderer = getRenderer().get();
    auto window = getWindow().get();
    auto event = getSDLEvent().get();

    int w, h; // texture width & height
    auto img = IMG_LoadTexture(renderer, "resources/background.jpg");
    SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    // I'm also scaling the texture 2x simply by setting the width and height
    SDL_Rect texr;
    texr.x = -50; texr.y = 100; texr.w = w; texr.h = h;

    /*while(1)
    {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        ctl->rotate();
                        break;
                    case SDLK_DOWN:
                        ctl->goDown();
                        break;
                    case SDLK_SPACE:
                        ctl->goStraightDown();
                        break;
                }
                break;
            default:;
        }

        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, img, NULL, &texr);
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(renderer);
    }*/

}

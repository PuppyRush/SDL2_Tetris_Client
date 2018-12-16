//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TGameController.h"
#include "TGame/TBoardController.h"

SDL_TETRIS

auto TDisplayController::getInstance()
{
    static auto inst = std::shared_ptr<TDisplayController>(new TDisplayController{});
    return inst;
}


Uint32 my_callbackfunc(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

void TDisplayController::_setDisplay()
{
    using namespace tetris;
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

    bool quit = true;

    SDL_TimerID my_timer_id = SDL_AddTimer(1000, my_callbackfunc, nullptr);

    auto ctl = BoardController::get();
    while (quit) {

        SDL_RenderCopy(renderer, img, NULL, &texr);

        auto board = ctl->getGameBoard();
        for (int y = 0 ; y < board.size() ; y++) {
            const auto &row = board.at(y);
            for (int x = 0 ; x < row.size() ; x++) {
                SDL_Point line[5];
                line[0].y = 50 + y * 30;
                line[0].x = 50 + x * 30;
                line[1].y = 50 + y * 30;
                line[1].x = 50 + x * 30 + 30;
                line[2].y = 50 + y * 30 + 30;
                line[2].x = 50 + x * 30 + 30;
                line[3].y = 50 + y * 30 + 30;
                line[3].x = 50 + x * 30;
                line[4].y = 50 + y * 30;
                line[4].x = 50 + x * 30;

                // Set render color to blue ( rect will be rendered in this color )
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                // Render rect
                SDL_RenderDrawLines(renderer, line, 5);
                // Render the rect to the screen

                if ( (board[y][x].getType() & UnitType::Fill) == UnitType::Fill) {
                    SDL_Rect rect;
                    rect.y = 50 + y * 30;
                    rect.x = 50 + x * 30;
                    rect.h = 30;
                    rect.w = 30;

                    SDL_RenderFillRect(renderer, &rect);
                    SDL_SetRenderDrawColor(renderer, 0, 80, 60, 255);
                    SDL_RenderDrawRect(renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(renderer);

        SDL_WaitEvent(event);
        switch (event->type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_LEFT:
                        ctl->goLeft();
                        break;
                    case SDLK_RIGHT:
                        ctl->goRight();
                        break;
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

        SDL_PollEvent(event);
        switch (event->type) {
            case SDL_USEREVENT: {
                /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
                ctl->goDown();
                break;
            }
                /* ... */
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    // cleanup SDL



    return ;
}

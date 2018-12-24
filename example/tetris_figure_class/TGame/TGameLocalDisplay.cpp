//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TGameLocalDisplay.h"
#include "TGame/TBoardController.h"

SDL_TETRIS


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

std::shared_ptr<TGameDisplay> TGameLocalDisplay::getInstance()
{
    static std::shared_ptr<TGameDisplay > inst = std::shared_ptr<TGameLocalDisplay>(new TGameLocalDisplay());
    return inst;
}

bool TGameLocalDisplay::clickedBack(const TDisplay disply)
{

}

bool TGameLocalDisplay::clickedStart()
{

}

bool TGameLocalDisplay::clickedSuspend()
{

}

void TGameLocalDisplay::_event(const SDL_Event* event) {

    switch (event->type) {
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    m_ctl->goLeft();
                    break;
                case SDLK_RIGHT:
                    m_ctl->goRight();
                    break;
                case SDLK_UP:
                    m_ctl->rotate();
                    break;
                case SDLK_DOWN:
                    m_ctl->goDown();
                    break;
                case SDLK_SPACE:
                    m_ctl->goStraightDown();
                    break;
            }
            break;
        case SDL_USEREVENT:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            m_ctl->goDown();
            break;
        case SDL_MOUSEBUTTONDOWN: {
            const TPoint point(event->button.x, event->button.y);
            if (clickedMenuEvent(point))
                break;
            break;
        }
        default:;
    }

    /* SDL_PollEvent(event);
      switch (event->type) {
          case SDL_USEREVENT:
              *//* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems *//*
                ctl->goDown();
                break;
                *//* ... *//*
        }
*/

}

void TGameLocalDisplay::_timer()
{
    SDL_TimerID my_timer_id = SDL_AddTimer(1000, my_callbackfunc, nullptr);
}

void TGameLocalDisplay::_draw()
{
    using namespace tetris;
    using namespace std;

    auto renderer = getRenderer().get();
    auto window = getWindow().get();

 /*   int w, h; // texture width & height
    auto img = IMG_LoadTexture(renderer, "resources/background.jpg");
    SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    // I'm also scaling the texture 2x simply by setting the width and height
    SDL_Rect texr;
    texr.x = -50; texr.y = 100; texr.w = w; texr.h = h;
    SDL_RenderCopy(renderer, img, NULL, &texr);

    bool quit = true;*/




    //draw board
    SDL_Rect rect;
    rect.y = GAMEBOARD_BEGIN_Y;
    rect.x = GAMEBOARD_BEGIN_X;
    rect.h = GAMEBOARD_DISPLAY_HEIGHT;
    rect.w = GAMEBOARD_DISPLAY_WIDTH;

    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);


    auto board = m_ctl->getGameBoard();
    for (int y = 0 ; y < board.size() ; y++) {
        const auto &row = board.at(y);
        for (int x = 0 ; x < row.size() ; x++) {
            SDL_Point line[5];
            line[0].y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN;
            line[0].x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN;
            line[1].y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN;
            line[2].y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN + GAMEBOARD_UNIT_LEN;
            line[2].x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN + GAMEBOARD_UNIT_LEN;
            line[3].y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN + GAMEBOARD_UNIT_LEN;
            line[1].x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN + GAMEBOARD_UNIT_LEN;
            line[3].x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN;
            line[4].y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN;
            line[4].x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN;

            // Set render color to blue ( rect will be rendered in this color )
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            // Render rect
            SDL_RenderDrawLines(renderer, line, 5);
            // Render the rect to the screen

            if ( (board[y][x].getType() & UnitType::Fill) == UnitType::Fill) {
                SDL_Rect rect;
                rect.y = GAMEBOARD_BEGIN_Y + y * GAMEBOARD_UNIT_LEN;
                rect.x = GAMEBOARD_BEGIN_X + x * GAMEBOARD_UNIT_LEN;
                rect.h = GAMEBOARD_UNIT_LEN;
                rect.w = GAMEBOARD_UNIT_LEN;

                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 80, 60, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }



}

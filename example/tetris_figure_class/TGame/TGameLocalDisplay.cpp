//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "TGameLocalDisplay.h"

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

void TGameLocalDisplay::_preInitialize()
{
    m_drawLine = TOptionManager::getInstance()->isDrawLine();

    auto ply = std::make_shared<TPlayer>();
    ply->setStartBoardPoint(TPoint{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
    ply->setBoardLength(FIGURE_UNIT_LEN);

    m_player.emplace_back(ply);
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

    auto& ply = m_player.front();

    switch (event->type) {
        case SDL_QUIT:
            setRun(false);
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    ply->goLeft();
                    break;
                case SDLK_RIGHT:
                    ply->goRight();
                    break;
                case SDLK_UP:
                    ply->rotate();
                    break;
                case SDLK_DOWN:
                    ply->goDown();
                    break;
                case SDLK_SPACE:
                    ply->goStraightDown();
                    break;
            }
            break;
        case SDL_USEREVENT:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            ply->goDown();
            break;
        case SDL_MOUSEBUTTONDOWN: {
            const TPoint point(event->button.x, event->button.y);
            if (clickedMenuEvent(point))
                break;
            break;
        }
        default:;
    }
}

void TGameLocalDisplay::_timer()
{
    SDL_TimerID my_timer_id = SDL_AddTimer(1000, my_callbackfunc, nullptr);
}

void TGameLocalDisplay::_draw()
{
    using namespace std;

    auto renderer = getRenderer().get();

    for(auto& ply : m_player)
    {
        auto board = ply->getBoard();
        const auto board_height = board.size();
        for (int y = 0 ; y < board_height ; y++) {
            const auto &row = board.at(y);
            const auto board_width = row.size();

            for (int x = 0 ; x < board_width ; x++)
            {
                if ( (board[y][x].getType() & UnitType::Fill) == UnitType::Fill)
                {
                    const auto color = board[y][x].getColor();
                    SDL_Rect rect;
                    rect.y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN;
                    rect.x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN;
                    rect.h = FIGURE_UNIT_LEN;
                    rect.w = FIGURE_UNIT_LEN;

                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , 255);
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderDrawRect(renderer, &rect);
                }

                if(m_drawLine) {
                    SDL_Point line[5];
                    line[0].x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN;
                    line[0].y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN;
                    line[1].x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN + FIGURE_UNIT_LEN;
                    line[1].y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN;
                    line[2].x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN + FIGURE_UNIT_LEN;
                    line[2].y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN + FIGURE_UNIT_LEN;
                    line[3].x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN;
                    line[3].y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN + FIGURE_UNIT_LEN;
                    line[4].x = GAMEBOARD_BEGIN_X + x * FIGURE_UNIT_LEN;
                    line[4].y = GAMEBOARD_BEGIN_Y + y * FIGURE_UNIT_LEN;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLines(renderer, line, 5);
                }
                else
                {
                    SDL_Point line[5];
                    line[0].x = GAMEBOARD_BEGIN_X ;
                    line[0].y = GAMEBOARD_BEGIN_Y ;
                    line[1].x = GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH;
                    line[1].y = GAMEBOARD_BEGIN_Y;
                    line[2].x = GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH;
                    line[2].y = GAMEBOARD_BEGIN_Y + GAMEBOARD_DISPLAY_HEIGHT;
                    line[3].x = GAMEBOARD_BEGIN_X;
                    line[3].y = GAMEBOARD_BEGIN_Y + GAMEBOARD_DISPLAY_HEIGHT;
                    line[4].x = GAMEBOARD_BEGIN_X;
                    line[4].y = GAMEBOARD_BEGIN_Y;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLines(renderer, line, 5);
                }


                const t_coord pred_x = GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN;
                const t_coord pred_y = GAMEBOARD_BEGIN_Y;

                SDL_Point line[5];
                line[0].x = pred_x;
                line[0].y = pred_y;
                line[1].x = pred_x + FIGURE_UNIT_LEN*4;
                line[1].y = pred_y;
                line[2].x = line[1].x;
                line[2].y = pred_y + FIGURE_UNIT_LEN*4;
                line[3].x = pred_x;
                line[3].y = line[2].y;
                line[4].x = line[0].x;
                line[4].y = line[0].y;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLines(renderer, line, 5);

            }
        }

    }

    auto& ply = m_player.front();
    auto nextFigrueBoard = ply->getNextFigureBoard();
    const auto nf_width = nextFigrueBoard.size();
    for(int y=0 ; y < nf_width ; y++)
    {
        const auto& row = nextFigrueBoard.at(y);
        const auto width = row.size();
        for(int x=0 ; x < width ; x++)
        {
            if ( (nextFigrueBoard[y][x].getType() & UnitType::Fill) == UnitType::Fill)
            {
                const auto color = nextFigrueBoard[y][x].getColor();

                SDL_Rect rect;
                rect.y = GAMEBOARD_BEGIN_Y +  y * FIGURE_UNIT_LEN;
                rect.x = GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN + x * FIGURE_UNIT_LEN;
                rect.h = FIGURE_UNIT_LEN;
                rect.w = FIGURE_UNIT_LEN;

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

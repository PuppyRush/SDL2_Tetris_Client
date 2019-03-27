//
// Created by chaed on 18. 12. 18.
//

#include "TGameDisplay.h"

SDL_TETRIS
using namespace sdleasygui;
using namespace sdleasygui;

TGameDisplay::TGameDisplay()
{}

void TGameDisplay::onKeyboardEvent (const SDL_KeyboardEvent* key)
{
    switch (key->type) {
        case SDL_KEYDOWN:
            if(!m_players.empty()) {
                m_players.front()->command(key->keysym.sym);
                refresh();
            }
            break;
        default:;
    }

    DisplayInterface::onKeyboardEvent(key);
}


void TGameDisplay::onUserEvent(const SDL_UserEvent* event) {

    switch (event->type) {
        case TETRIS_EVENT_FIGURETIMER:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            if(!m_players.empty()) {
                m_players.front()->command(SDLK_DOWN);
                refresh();
            }
            break;
        default:;
    }

    DisplayInterface::onUserEvent(event);
}

void TGameDisplay::onClose()
{
    m_players.clear();
    SDL_RemoveTimer(m_figureTimer);

    DisplayInterface::onClose();
}

void TGameDisplay::onCreate()
{

    DisplayInterface::onCreate();
}

void TGameDisplay::onDraw()
{
    using namespace std;

    if(!m_gamestart)
        return;

    auto renderer = getRenderer();

    for(const auto& playerPtr : m_players)
    {
        auto& ply = *playerPtr.get();
        const auto board = ply.getController().getBoard();
        const auto beginX = board->getStartDisplayPoint().x;
        const auto beginY = board->getStartDisplayPoint().y;
        const auto figureLen = board->getblockLength();


        SDL_Point line[5];
        line[0].x = beginX ;
        line[0].y = beginY ;
        line[1].x = beginX + GAMEBOARD_DISPLAY_WIDTH;
        line[1].y = beginY;
        line[2].x = beginX + GAMEBOARD_DISPLAY_WIDTH;
        line[2].y = beginY + GAMEBOARD_DISPLAY_HEIGHT;
        line[3].x = beginX;
        line[3].y = beginY + GAMEBOARD_DISPLAY_HEIGHT;
        line[4].x = beginX;
        line[4].y = beginY;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLines(renderer, line, 5);


        const t_coord pred_x = beginX + GAMEBOARD_DISPLAY_WIDTH + figureLen;
        const t_coord pred_y = beginY;
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

        _drawFigure(board, ply.getController().getCurrentFigure());
        _drawFigure(board, ply.getController().getGhostFigure());


        const auto gameboard = board->getBoard();
        constexpr const auto board_height = gameboard.size();
        for (int y = 0 ; y < board_height ; y++) {

            const auto board_width = gameboard[y].size();
            for (int x = 0 ; x < board_width ; x++)
            {
                auto unit = gameboard[y][x];
                if(unit.getType() & UnitType::Fixed)
                {
                    SDL_Rect rect{beginX + x * figureLen,
                                  beginY + y * figureLen,
                                  figureLen ,figureLen};

                    const auto color = unit.getColor();
                    auto renderer = getRenderer();
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderDrawRect(renderer, &rect);
                }

                if(m_drawLine) {
                    SDL_Point line[5];
                    line[0].x = beginX + x * figureLen;
                    line[0].y = beginY + y * figureLen;
                    line[1].x = beginX + x * figureLen + figureLen;
                    line[1].y = beginY + y * figureLen;
                    line[2].x = beginX + x * figureLen + figureLen;
                    line[2].y = beginY + y * figureLen + figureLen;
                    line[3].x = beginX + x * figureLen;
                    line[3].y = beginY + y * figureLen + figureLen;
                    line[4].x = beginX + x * figureLen;
                    line[4].y = beginY + y * figureLen;
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLines(renderer, line, 5);
                }
            }
        }
    }

    _drawNextFigure();
}

void TGameDisplay::_drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure)
{
    const auto beginX = board->getStartDisplayPoint().x;
    const auto beginY = board->getStartDisplayPoint().y;
    const auto figureLen = board->getblockLength();

    for(const auto coord : figure->getCoords())
    {
        const int x = coord.getPoint().x;
        const int y = coord.getPoint().y;
        const auto color = coord.getColor();
        SDL_Rect rect{beginX + x * figureLen,
                      beginY + y * figureLen,
                      figureLen ,figureLen};

        auto renderer = getRenderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}


void TGameDisplay::_drawNextFigure()
{
    using namespace std;
    auto renderer = getRenderer();

    //next figure
    const auto& ply = m_players.front();
    const auto board = ply->getController().getNextFigureBoard();
    const auto nextFigure = ply->getController().getNextFigure();

    const auto beginX = board->getStartDisplayPoint().x;
    const auto beginY = board->getStartDisplayPoint().y;
    const auto figureLen = board->getblockLength();

    for(const auto coord : nextFigure->getCoords())
    {
        const int x = coord.getPoint().x;
        const int y = coord.getPoint().y;
        const auto color = coord.getColor();
        SDL_Rect rect{beginX + x * figureLen,
                      beginY + y * figureLen,
                      figureLen ,figureLen};

        auto renderer = getRenderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "SDLEasyGUI/Controller/Button.h"
#include "TGameLocalDisplay.h"

SDL_TETRIS


Uint32 my_callbackfunc(Uint32 interval, void *param) {

    SDL_UserEvent userevent;
    userevent.type = TETRIS_EVENT_FIGURETIMER;
    userevent.code = 0;

    SDL_Event event;
    event.type = TETRIS_EVENT_FIGURETIMER;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

std::shared_ptr<TGameDisplay> TGameLocalDisplay::getInstance()
{
    static std::shared_ptr<TGameDisplay > inst = std::shared_ptr<TGameLocalDisplay>(new TGameLocalDisplay());
    return inst;
}

void TGameLocalDisplay::onPreInitialize()
{
    auto ply = std::make_shared<TPlayer>();
    m_player.emplace_back(ply);

    for(auto& ply : m_player)
    {
        ply->startGame();
    }
    auto board = ply->getController()->getBoard();

    m_drawLine = TOptionManager::getInstance()->isDrawLine();

    board->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
    board->setblockLength(FIGURE_UNIT_LEN);

    auto nextboard = ply->getController()->getNextFigureBoard();
    nextboard->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN, GAMEBOARD_BEGIN_Y});
    nextboard->setblockLength(FIGURE_UNIT_LEN);

    t_size begin_y = WINDOW_HEIGHT/10*3;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true)->
            display(TDisplay::Main);

        addControll(Button::getInstance(bld));
    }
}

void TGameLocalDisplay::onClose()
{
    m_player.clear();
    SDL_RemoveTimer(m_figureTimer);

    DisplayInterface::onClose();
}

void TGameLocalDisplay::onCreate()
{

    DisplayInterface::onCreate();
}

bool TGameLocalDisplay::onClickedBack(const TDisplay disply)
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
            _refresh();
            break;
        case SDL_KEYDOWN:
            ply->getController()->command(event->key.keysym.sym);
            _refresh();
            break;
        case TETRIS_EVENT_FIGURETIMER:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            ply->getController()->command(SDLK_DOWN);
            _refresh();
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            const TPoint point(event->button.x, event->button.y);
            if (clickedMenuEvent(point))
                break;
            _refresh();
            break;
        }
        default:;
    }

    DisplayInterface::_event(event);
}

void TGameLocalDisplay::_timer()
{
    m_figureTimer = SDL_AddTimer(1000, my_callbackfunc, nullptr);
}

void TGameLocalDisplay::onDraw()
{
    using namespace std;

    auto renderer = getRenderer().get();

    for(const auto& playerPtr : m_player)
    {
        const auto& ply = *playerPtr.get();
        const auto board = ply.getController()->getBoard();
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

        _drawFigure(board, ply.getController()->getCurrentFigure());
        _drawFigure(board, ply.getController()->getGhostFigure());


        const auto gameboard = board->getBoard();
        constexpr const auto board_height = gameboard.size();
        for (int y = 0 ; y < board_height ; y++) {

            const auto board_width = gameboard[y].size();
            for (int x = 0 ; x < board_width ; x++)
            {
                auto unit = gameboard[y][x];
                if(unit.getType() & UnitType::Fill)
                {
                    SDL_Rect rect{beginX + x * figureLen,
                                  beginY + y * figureLen,
                                  figureLen ,figureLen};

                    const auto color = unit.getColor();
                    auto renderer = getRenderer().get();
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

void TGameLocalDisplay::_drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure)
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

        auto renderer = getRenderer().get();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}


void TGameLocalDisplay::_drawNextFigure()
{
    using namespace std;
    auto renderer = getRenderer().get();

    //next figure
    const auto& ply = m_player.front();
    const auto board = ply->getController()->getNextFigureBoard();
    const auto nextFigure = ply->getController()->getNextFigure();

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

        auto renderer = getRenderer().get();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
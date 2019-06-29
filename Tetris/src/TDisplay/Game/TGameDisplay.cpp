//
// Created by chaed on 18. 12. 18.
//

#include <string>

#include "TGameDisplay.h"
#include "SDL2EasyGUI/include/Button.h"
#include "TResource.h"
//#include "GameInterface/include/JsonHelper.h"
#include "GameInterface/include/Packet.h"

SDL_TETRIS
using namespace game_interface;
using namespace sdleasygui;
using namespace tetris_module;
using namespace std;

TGameDisplay::TGameDisplay(const sdleasygui::t_id displayId)
        : TDisplayInterface(displayId)
{
    m_gameTimer = make_shared<TimerAdder>(1000, game_interface::toUType(TetrisEvent::TETRIS_EVENT_FIGURETIMER));
    m_gameTimer->windowsId(this->getWindowID());
}

void TGameDisplay::onKeyboardEvent(const SDL_KeyboardEvent* key)
{
    switch (key->type) {
        case SDL_KEYDOWN:
            if (!m_players.empty()) {
                m_players.front()->command(key->keysym.sym);
                refresh();
            }
            break;
        default:;
    }

    TDisplayInterface::onKeyboardEvent(key);
}

void TGameDisplay::onTimerEvent(const SDL_UserEvent* user)
{
    switch (user->code) {
        case TETRIS_EVENT_FIGURETIMER:
            /* and now we can call the function we wanted to call in the timer but couldn't because of the multithreading problems */
            if (!m_players.empty()) {
                refresh();
                m_players.front()->command(SDLK_DOWN);
            }

            break;
        default:;
    }

    TDisplayInterface::onTimerEvent(user);
}

void TGameDisplay::onUserEvent(const SDL_UserEvent* event)
{

    TDisplayInterface::onUserEvent(event);
}

void TGameDisplay::onInitialize()
{
    setBackgroundColor(ColorCode::darkgray);


    m_gameroom->initialize();

    auto& ply = TPlayer::getInstance();
    ply->startGame();

    //임시 코드. 수정 필요!!!!
    m_players.emplace_back(ply);

    TDisplayInterface::onInitialize();
}

void TGameDisplay::onClose()
{
    m_players.clear();
    SDL_RemoveTimer(m_timerId);

    TDisplayInterface::onClose();
}

void TGameDisplay::onCreate()
{

    TDisplayInterface::onCreate();
}

void TGameDisplay::onClickedStart(const void* click)
{
    m_timerId = m_gameTimer->addTimer();

    m_gamestart = true;

    auto ctl = getControll<Button>(resource::GAME_START);
    ctl->setEnabled(false);
}

void TGameDisplay::onDraw()
{
    using namespace std;

    // if(!m_gamestart)
    //    return;

    auto renderer = getRenderer();

    for (const auto& playerPtr : m_players) {
        auto& ply = *playerPtr.get();
        const auto board = ply.getController().getBoard();
        const auto beginX = board->getStartDisplayPoint().x;
        const auto beginY = board->getStartDisplayPoint().y;
        const auto figureLen = board->getblockLength();

        SDL_Point line[5];
        line[0].x = beginX;
        line[0].y = beginY;
        line[1].x = beginX + GAMEBOARD_DISPLAY_WIDTH;
        line[1].y = beginY;
        line[2].x = beginX + GAMEBOARD_DISPLAY_WIDTH;
        line[2].y = beginY + GAMEBOARD_DISPLAY_HEIGHT;
        line[3].x = beginX;
        line[3].y = beginY + GAMEBOARD_DISPLAY_HEIGHT;
        line[4].x = beginX;
        line[4].y = beginY;

        SDL_SetRenderDrawColor(renderer,
                board->getBackgroundColor().r, board->getBackgroundColor().g,
                board->getBackgroundColor().b, board->getBackgroundColor().a);
        SDL_RenderDrawLines(renderer, line, 5);

        const t_coord pred_x = beginX + GAMEBOARD_DISPLAY_WIDTH + figureLen;
        const t_coord pred_y = beginY;
        line[0].x = pred_x;
        line[0].y = pred_y;
        line[1].x = pred_x + FIGURE_UNIT_LEN * 4;
        line[1].y = pred_y;
        line[2].x = line[1].x;
        line[2].y = pred_y + FIGURE_UNIT_LEN * 4;
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
        for (int y = 0; y < board_height; y++) {

            const auto board_width = gameboard[y].size();
            for (int x = 0; x < board_width; x++) {
                auto unit = gameboard[y][x];
                if (unit.getType() & UnitType::Fixed) {
                    SDL_Rect rect{beginX + x * figureLen,
                                  beginY + y * figureLen,
                                  figureLen, figureLen};

                    const auto color = unit.getColor();
                    auto renderer = getRenderer();
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_RenderDrawRect(renderer, &rect);
                }

                if (m_drawLine) {
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

    TDisplayInterface::onDraw();
}

void TGameDisplay::_drawFigure(TFigureController::board_ptr board, TFigureController::figure_ptr figure)
{
    const auto beginX = board->getStartDisplayPoint().x;
    const auto beginY = board->getStartDisplayPoint().y;
    const auto figureLen = board->getblockLength();

    for (const auto coord : figure->getCoords()) {
        const int x = coord.getPoint().x;
        const int y = coord.getPoint().y;
        const auto color = coord.getColor();
        SDL_Rect rect{beginX + x * figureLen,
                      beginY + y * figureLen,
                      figureLen, figureLen};

        auto renderer = getRenderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void TGameDisplay::_drawNextFigure()
{
    using namespace std;
    auto renderer = getRenderer();

    if (m_players.empty()) {
        return;
    }

    //next figure
    const auto& ply = m_players.front();
    const auto board = ply->getController().getNextFigureBoard();
    const auto nextFigure = ply->getController().getNextFigure();

    const auto beginX = board->getStartDisplayPoint().x;
    const auto beginY = board->getStartDisplayPoint().y;
    const auto figureLen = board->getblockLength();

    for (const auto coord : nextFigure->getCoords()) {
        const int x = coord.getPoint().x;
        const int y = coord.getPoint().y;
        const auto color = coord.getColor();
        SDL_Rect rect{beginX + x * figureLen,
                      beginY + y * figureLen,
                      figureLen, figureLen};

        auto renderer = getRenderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
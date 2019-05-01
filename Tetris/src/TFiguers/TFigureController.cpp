//
// Created by chaed on 19. 2. 4.
//

#include "TFigureController.h"
#include "TFigureBuilder.h"

SDL_TETRIS

using namespace std;
using namespace sdleasygui;

TFigureController::TFigureController()
        : m_currentFigure(nullptr),
          m_nextFigure(nullptr),
          m_board(make_shared<board_type>()),
          m_nextFigureBoard(make_shared<nextfigure_board_type>())
{

    createNextFigureRandomly();

    m_board->_setCoords(m_currentFigure);
    m_board->setGhostFigure(m_currentFigure, m_ghostFigure);
}

void TFigureController::createNextFigureRandomly()
{
    if (m_currentFigure.get() == nullptr) {
        TFigureBuilder bld{TPoint{GAMEBOARD_WIDTH_COUNT / 2 - 1, 2}};
        bld.unitType(UnitType::Moving);
        m_currentFigure = bld.build();

        TFigureBuilder bld2{TPoint{1, 2}};
        bld2.unitType(UnitType::Moving);
        m_nextFigure = bld2.build();
    } else {

        m_nextFigureBoard->_eraseCoords(m_nextFigure);

        m_currentFigure = m_nextFigure->copy();
        m_currentFigure->setPoint(TPoint(GAMEBOARD_WIDTH_COUNT / 2 - 1, 2));
        m_nextFigure.reset();

        TFigureBuilder bld{TPoint{1, 2}};
        bld.unitType(UnitType::Moving);
        m_nextFigure = bld.build();
    }

    m_nextFigureBoard->_setCoords(m_nextFigure);
}

void TFigureController::command(const t_eventType event)
{
    switch (event) {
        case SDLK_LEFT:
            _goLeft(event);
            break;
        case SDLK_RIGHT:
            _goRight(event);
            break;
        case SDLK_UP:
            _rotate(event);
            break;
        case SDLK_DOWN:
            _goDown(event);
            break;
        case SDLK_SPACE:
            _goStraightDown(event);
            break;
    }

    m_board->setGhostFigure(m_currentFigure, m_ghostFigure);
}

void TFigureController::_goStraightDown(const sdleasygui::t_eventType event)
{
    m_board->_eraseCoords(m_currentFigure);

    shared_ptr<TFigure> copied(nullptr);
    while (m_board->_isValidation(m_currentFigure)) {
        copied = m_currentFigure->move(event);
    }

    if (copied) {
        m_currentFigure = copied;
        m_currentFigure->setAll(UnitType::Fixed);
        m_board->_setCoords(m_currentFigure);
    }

    m_board->_eraseLinesIfFillLineThenCollapse();

    createNextFigureRandomly();
    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_rotate(const sdleasygui::t_eventType event)
{
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->move(event);

    while (m_board->isHit(m_currentFigure->getLeftmost())) {
        m_currentFigure->move(SDLK_RIGHT);
    }

    while (m_board->isHit(m_currentFigure->getRightmost())) {
        m_currentFigure->move(SDLK_LEFT);
    }

    if (!m_board->_isValidation(m_currentFigure)) {
        m_currentFigure = copied;
    }

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goDown(const sdleasygui::t_eventType event)
{
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->move(event);

    if (!m_board->_isValidation(m_currentFigure)) {
        m_currentFigure = copied;
        m_currentFigure->setAll(UnitType::Fixed);
        m_board->_setCoords(m_currentFigure);
        createNextFigureRandomly();
    }

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goLeft(const sdleasygui::t_eventType event)
{
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->move(event);
    if (!m_board->_isValidation(m_currentFigure)) {
        m_currentFigure = copied;
    }

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goRight(const sdleasygui::t_eventType event)
{
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->move(event);
    if (!m_board->_isValidation(m_currentFigure)) {
        m_currentFigure = copied;
    }

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::forceSet(const TFigure* fig)
{
    m_board->_eraseCoords(m_currentFigure);

    m_currentFigure.reset();
    m_currentFigure = fig->copy();

    m_board->_setCoords(m_currentFigure);
}

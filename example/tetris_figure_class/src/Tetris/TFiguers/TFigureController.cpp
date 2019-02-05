//
// Created by chaed on 19. 2. 4.
//

#include "TFigureController.h"
#include "TFigureBuilder.h"

SDL_TETRIS

TFigureController::TFigureController()
:m_currentFigure(nullptr),
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
    if(m_currentFigure.get() == nullptr)
    {
        TFigureBuilder bld{TPoint{GAMEBOARD_WIDTH_COUNT / 2 - 1, 2}};
        bld.unitType(UnitType::Figure);
        m_currentFigure = bld.build();

        TFigureBuilder bld2{TPoint{1,2}};
        bld2.unitType(UnitType::Figure);
        m_nextFigure = bld2.build();
    }
    else{

        m_nextFigureBoard->_eraseCoords(m_nextFigure);

        m_currentFigure = m_nextFigure->copy();
        m_currentFigure->setPoint(TPoint(GAMEBOARD_WIDTH_COUNT / 2 - 1, 2));
        m_nextFigure.reset();

        TFigureBuilder bld{TPoint{1,2}};
        bld.unitType(UnitType::Figure);
        m_nextFigure = bld.build();
    }

    m_nextFigureBoard->_setCoords(m_nextFigure);
}

void TFigureController::command(const t_eventType event)
{
    switch (event)
    {
        case SDLK_LEFT:
            _goLeft();
            break;
        case SDLK_RIGHT:
            _goRight();
            break;
        case SDLK_UP:
            _rotate();
            break;
        case SDLK_DOWN:
            _goDown();
            break;
        case SDLK_SPACE:
            _goStraightDown();
            break;
    }

    m_board->setGhostFigure(m_currentFigure, m_ghostFigure);
}

void TFigureController::_goStraightDown()
{
    m_board->_eraseCoords(m_currentFigure);

    std::shared_ptr<TFigure> copied(nullptr);
    while(m_board->_isValidation(m_currentFigure))
    {
        copied = m_currentFigure->goDown();
    }

    if(copied)
    {
        m_currentFigure = copied;
        m_currentFigure->setAll(UnitType::Fill);
        m_board->_setCoords(m_currentFigure);
    }

    m_board->_eraseLinesIfFillLineThenCollapse();

    createNextFigureRandomly();
    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_rotate() {
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->rotateLeft();

    while(m_board->isHit(m_currentFigure->getLeftmost()))
    {
        m_currentFigure->goRight();
    }

    while(m_board->isHit(m_currentFigure->getRightmost()))
    {
        m_currentFigure->goLeft();
    }

    if(!m_board->_isValidation(m_currentFigure))
        m_currentFigure = copied;

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goDown() {
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->goDown();

    if (!m_board->_isValidation(m_currentFigure)) {
        m_currentFigure = copied;
        m_currentFigure->setAll(UnitType::Fill);
        m_board->_setCoords(m_currentFigure);
        createNextFigureRandomly();
    }

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goLeft() {
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->goLeft();
    if (!m_board->_isValidation(m_currentFigure))
        m_currentFigure = copied;

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::_goRight() {
    m_board->_eraseCoords(m_currentFigure);

    auto copied = m_currentFigure->goRight();
    if (!m_board->_isValidation(m_currentFigure))
        m_currentFigure = copied;

    m_board->_setCoords(m_currentFigure);
}

void TFigureController::clear()
{
    delete this;
    /*m_board->clear();
    m_nextFigureBoard->clear();
    m_currentFigure.reset();
    m_nextFigure.reset();
    m_ghostFigure.reset();*/
}

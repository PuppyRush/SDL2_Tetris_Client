//
// Created by chaed on 18. 11. 24.
//

#include <random>
#include <algorithm>
#include <set>

#include "../Common/TypeTraits.h"

#include "TFigureBoard.h"
#include "TFigureBuilder.h"

SDL_TETRIS

TFigureBoard::TFigureBoard()
    : m_currentFigure(nullptr),
    m_nextFigure(nullptr)
{
    createNextFigureRandomly();
    _setCoords();

    for (int i = 0 ; i < m_board.size() ; i++) {
        auto board = m_board[i];
        for (int l = 0 ; l < board.size() ; l++) {
            board[l] = TFigureUnit(TPoint(i, l), 0, TColorCode::none, UnitType::Empty);
        }
    }
}

void TFigureBoard::createNextFigureRandomly()
{
    if(m_currentFigure.get() == nullptr)
    {
        TFigureBuilder *bld = new TFigureBuilder(TPoint(GAMEBOARD_WIDTH_COUNT / 2 - 1, 2));
        m_currentFigure = bld->build();

        TFigureBuilder *bld2 = new TFigureBuilder(TPoint(1,2));
        m_nextFigure = bld2->build();
    }
    else{

        _eraseNextFigureCoords();

        m_currentFigure = m_nextFigure;
        m_currentFigure->setPoint(TPoint(GAMEBOARD_WIDTH_COUNT / 2 - 1, 2));
        m_nextFigure.reset();

        TFigureBuilder *bld = new TFigureBuilder(TPoint(1,2));
        m_nextFigure = bld->build();
    }

    _setNextFigureCoords();
}

std::shared_ptr<TFigure> TFigureBoard::getCurrentFigure() {
    return m_currentFigure;
}

std::shared_ptr<TFigureBoard> TFigureBoard::getInstance() {
    static auto board = std::shared_ptr<TFigureBoard>(new TFigureBoard());
    return board;
}

void TFigureBoard::goStraightDown()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    _eraseCoords();

    std::shared_ptr<TFigure> copied(nullptr);
    while(_isValidation(m_currentFigure.get()))
    {
        copied = m_currentFigure->goDown();
    }

    if(copied)
    {
        m_currentFigure = copied;
        _setCoords();
    }

    _eraseLinesIfFillLineThenCollapse();

    createNextFigureRandomly();
    _setCoords();
}

void TFigureBoard::rotate() {
    std::lock_guard<std::mutex> lock(m_mutex);

    _eraseCoords();

    auto copied = m_currentFigure->rotateLeft();
    if (!_isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    _setCoords();
}

void TFigureBoard::goDown() {
    std::lock_guard<std::mutex> lock(m_mutex);

    _eraseCoords();

    auto copied = m_currentFigure->goDown();

    if (!_isValidation(m_currentFigure.get())) {
        m_currentFigure = copied;
        _setCoords();
        createNextFigureRandomly();
    }

    _setCoords();
}

void TFigureBoard::goLeft() {
    std::lock_guard<std::mutex> lock(m_mutex);

    _eraseCoords();

    auto copied = m_currentFigure->goLeft();
    if (!_isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    _setCoords();
}

void TFigureBoard::goRight() {
    std::lock_guard<std::mutex> lock(m_mutex);

    _eraseCoords();

    auto copied = m_currentFigure->goRight();
    if (!_isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    _setCoords();
}

const bool TFigureBoard::_isValidation(const TFigure *destFigure) {

    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;

        if (y < 0 || y >= GAMEBOARD_HEIGHT_COUNT  || x < 0 || x >= GAMEBOARD_WIDTH_COUNT)
            return false;

        if ( (m_board[y][x].getType() & UnitType::Fill) == UnitType::Fill)
            return false;
    }

    return true;
}

void TFigureBoard::_eraseCoords() {
    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_board[y][x].setType(UnitType::Empty);
    }
}

void TFigureBoard::_setCoords() {
    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_board[y][x].setType(UnitType::Fill);
        m_board[y][x].setColor(m_currentFigure->getColor());
    }
}

void TFigureBoard::_setNextFigureCoords()
{
    for (const auto coord : m_nextFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_nextFigureBoard[y][x].setType(UnitType::Fill);
        m_nextFigureBoard[y][x].setColor(m_nextFigure->getColor());
    }
}

void TFigureBoard::_eraseNextFigureCoords()
{
    for (const auto coord : m_nextFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_nextFigureBoard[y][x].setType(UnitType::Empty);
    }
}

bool TFigureBoard::_eraseLinesIfFillLineThenCollapse()
{
    std::set<tetris::t_coord, std::greater<t_coord>> collapseHeights;
    for(t_coord y = GAMEBOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
    {
        int x=0;
        for(; x < GAMEBOARD_WIDTH_COUNT ; ++x)
        {
            if( (m_board[y][x].getType() & UnitType ::Empty) == UnitType ::Empty)
                break;
        }
        if(x==GAMEBOARD_WIDTH_COUNT) {
            collapseHeights.insert(y);
            for(int x=0; x < GAMEBOARD_WIDTH_COUNT ; ++x)
            {
                m_board[y][x].setType(UnitType::Empty);
            }
        }
    }

    if(collapseHeights.empty())
        return false;

    for(t_coord x=0 ; x < GAMEBOARD_WIDTH_COUNT ; ++x)
    {
        for(t_coord y = GAMEBOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
        {
            if( ( m_board[y][x].getType() & UnitType ::Fill) == UnitType ::Fill)
            {
                const size_t removedCnt = std::count_if(collapseHeights.begin(), collapseHeights.end(),
                    [y](const auto _y){
                        return y < _y;
                    });

                if(removedCnt>0)
                {
                    m_board[y+removedCnt][x].setType(UnitType::Fill);
                    m_board[y+removedCnt][x].setColor(m_board[y][x].getColor());
                    m_board[y][x].setType(UnitType::Empty);
                    m_board[y][x].setColor(TColorCode::none);
                }
            }
        }
    }

    return true;
}
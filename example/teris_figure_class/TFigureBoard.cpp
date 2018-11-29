//
// Created by chaed on 18. 11. 24.
//

#include <random>
#include <algorithm>
#include <set>

#include "TypeTraits.h"
#include "TFigureBoard.h"
#include "TFigureBuilder.h"
#include "TFigureLBuilder.h"
#include "TFigureL.h"

using namespace tetris;

TFigureBoard::TFigureBoard()
    : m_currentFigure(nullptr) {
    createNextFigureRandomly();

    for (int i = 0 ; i < m_board.size() ; i++) {
        auto board = m_board[i];
        for (int l = 0 ; l < board.size() ; l++) {
            board[l] = TFigureUnit(TPoint(i, l), 0, TColor::none, TFigureUnit::UnitType::Empty);
        }
    }
}

void TFigureBoard::createNextFigureRandomly() {
    if (m_currentFigure) {
        m_currentFigure.reset();
    }

    switch (EnumHelper<TFigureClass>::getRandomly()) {
        case TFigureClass::L: {
            TFigureBuilder *bld = new TFigureLBuilder(TPoint(BOARD_WIDTH_COUNT/2-1, 2));
            bld->type(TFigureType::A);
            m_currentFigure = TFigureL::get(bld);
        }
            break;
    }

    setCoords();
}

std::shared_ptr<TFigure> TFigureBoard::getCurrentFigure() {
    return m_currentFigure;
}

std::shared_ptr<TFigureBoard> TFigureBoard::get() {
    static auto board = std::shared_ptr<TFigureBoard>(new TFigureBoard());
    return board;
}

void TFigureBoard::goStraightDown()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    eraseCoords();

    std::shared_ptr<TFigure> copied(nullptr);
    while(isValidation(m_currentFigure.get()))
    {
        copied = m_currentFigure->goDown();
    }

    if(copied)
    {
        m_currentFigure = copied;
        setCoords();
    }

    eraseLineIfFillLinesAndThenCollapse();

    createNextFigureRandomly();
    setCoords();
}

void TFigureBoard::rotate() {
    std::lock_guard<std::mutex> lock(m_mutex);

    eraseCoords();

    auto copied = m_currentFigure->rotateLeft();
    if (!isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    setCoords();
}

void TFigureBoard::goDown() {
    std::lock_guard<std::mutex> lock(m_mutex);

    eraseCoords();

    auto copied = m_currentFigure->goDown();

    if (!isValidation(m_currentFigure.get())) {
        m_currentFigure = copied;
        setCoords();
        createNextFigureRandomly();
    }

    setCoords();

    //if(eraseLineIfFillLinesAndThenCollapse())
    //    eraseCoords();
}

void TFigureBoard::goLeft() {
    std::lock_guard<std::mutex> lock(m_mutex);

    eraseCoords();

    auto copied = m_currentFigure->goLeft();
    if (!isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    setCoords();
}

void TFigureBoard::goRight() {
    std::lock_guard<std::mutex> lock(m_mutex);

    eraseCoords();

    auto copied = m_currentFigure->goRight();
    if (!isValidation(m_currentFigure.get()))
        m_currentFigure = copied;

    setCoords();
}

const bool TFigureBoard::isValidation(const TFigure *destFigure) {

    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;

        if (y < 0 || y >= BOARD_HEIGHT_COUNT  || x < 0 || x >= BOARD_WIDTH_COUNT)
            return false;

        if (m_board[y][x].getType() == TFigureUnit::UnitType::Fill)
            return false;
    }

    return true;
}

void TFigureBoard::eraseCoords() {
    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_board[y][x].setType(TFigureUnit::UnitType::Empty);
        m_board[y][x].setColor(TColor::none);
    }
}

void TFigureBoard::setCoords() {
    for (const auto coord : m_currentFigure->getCoords()) {
        const auto x = coord.getPoint().x;
        const auto y = coord.getPoint().y;
        m_board[y][x].setType(TFigureUnit::UnitType::Fill);
        m_board[y][x].setColor(coord.getColor());
    }
}

bool TFigureBoard::eraseLineIfFillLinesAndThenCollapse()
{
    std::set<tetris::t_coord, std::greater<t_coord>> collapseHeights;
    for(t_coord y = BOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
    {
        int x=0;
        for(; x < BOARD_WIDTH_COUNT ; ++x)
        {
            if(m_board[y][x].getType() == TFigureUnit::UnitType ::Empty)
                break;
        }
        if(x==BOARD_WIDTH_COUNT) {
            collapseHeights.insert(y);
            for(int x=0; x < BOARD_WIDTH_COUNT ; ++x)
            {
                m_board[y][x].setType(TFigureUnit::UnitType::Empty);
                m_board[y][x].setColor(TColor::none);
            }
        }
    }

    if(collapseHeights.empty())
        return false;

    for(t_coord x=0 ; x < BOARD_WIDTH_COUNT ; ++x)
    {
        for(t_coord y = BOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
        {
            if(m_board[y][x].getType() == TFigureUnit::UnitType ::Fill)
            {
                const size_t removedCnt = std::count_if(collapseHeights.begin(), collapseHeights.end(),
                    [y](const auto _y){
                        return y < _y;
                    });

                if(removedCnt>0)
                {
                    m_board[y+removedCnt][x].setType(TFigureUnit::UnitType::Fill);
                    m_board[y+removedCnt][x].setColor(m_board[y][x].getColor());
                    m_board[y][x].setType(TFigureUnit::UnitType::Empty);
                    m_board[y][x].setColor(TColor::none);
                }
            }
        }
    }

    return true;
}
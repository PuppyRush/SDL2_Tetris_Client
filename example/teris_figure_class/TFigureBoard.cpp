//
// Created by chaed on 18. 11. 24.
//

#include <random>
#include <algorithm>

#include "TypeTraits.h"
#include "TFigureBoard.h"
#include "TFigureBuilder.h"
#include "TFigureLBuilder.h"
#include "TFigureL.h"

using namespace tetris;

TFigureBoard::TFigureBoard ()
    : m_currentFigure (nullptr)
{
    createNextFigureRandomly ();
    
    for(int i=0 ; i < m_board.size() ; i++)
    {
        auto board = m_board[i];
        for (int l = 0; l < board.size(); l++)
        {
            board[l] = TFigureUnit (TPoint (i, l), 0, TColor::none, TFigureUnit::UnitType::Empty);
        }
    }
}

void TFigureBoard::createNextFigureRandomly ()
{
    if (m_currentFigure)
    {
        m_currentFigure.reset ();
    }
    
    switch (EnumHelper<TFigureClass>::getRandomly ())
    {
        case TFigureClass::L:
        {
            TFigureBuilder *bld = new TFigureLBuilder (TPoint (3, 5));
            bld->type (TFigureType::A);
            m_currentFigure = TFigureL::get (bld);
        }
        break;
    }
    
    setCoords();
}

std::shared_ptr<TFigure> TFigureBoard::getCurrentFigure ()
{
    return m_currentFigure;
}

std::shared_ptr<TFigureBoard> TFigureBoard::get ()
{
    static auto board = std::shared_ptr<TFigureBoard> (new TFigureBoard ());
    return board;
}

void TFigureBoard::rotate ()
{
    eraseCoords();
    
    m_currentFigure->rotateLeft ();
    //if (!isValidation (m_currentFigure.get ()))
    //    m_currentFigure = copied;
    
    setCoords();
}

void TFigureBoard::goDown ()
{
    eraseCoords();
    
    auto copied = m_currentFigure->goDown ();
    
    if (!isValidation (m_currentFigure.get ()))
        m_currentFigure = copied;
    
    setCoords();
}

void TFigureBoard::goLeft ()
{
    eraseCoords();
    
    auto copied = m_currentFigure->goLeft ();
    if (!isValidation (m_currentFigure.get ()))
        m_currentFigure = copied;
    
    setCoords();
}

void TFigureBoard::goRight ()
{
    eraseCoords();
    
    auto copied = m_currentFigure->goRight ();
    if (!isValidation (m_currentFigure.get ()))
        m_currentFigure = copied;
    
    setCoords();
}

const bool TFigureBoard::isValidation (const TFigure *destFigure)
{
    return true;
    for(const auto coord : m_currentFigure->getCoords ())
    {
        //m_board[coord.getPoint ().y][coord.getPoint ().x]
    }
}

void TFigureBoard::eraseCoords()
{
    for(const auto coord : m_currentFigure->getCoords ())
    {
        const auto x = coord.getPoint ().x;
        const auto y = coord.getPoint ().y;
        m_board[y][x].setType (TFigureUnit::UnitType::Empty);
        m_board[y][x].setColor (TColor::none);
    }
}

void TFigureBoard::setCoords()
{
    for(const auto coord : m_currentFigure->getCoords ())
    {
        const auto x = coord.getPoint ().x;
        const auto y = coord.getPoint ().y;
        m_board[y][x].setType (TFigureUnit::UnitType::Fill);
        m_board[y][x].setColor (coord.getColor ());
    }
}

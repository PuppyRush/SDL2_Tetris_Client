//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_FIGUREBOARD_H
#define TERIS_FIGURE_CLASS_FIGUREBOARD_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <array>
#include <memory>
#include <cassert>
#include <exception>
#include <random>
#include <algorithm>
#include <set>


#include "TFigure.h"
#include "Tetris/Common/TProperty.h"

SDL_TETRIS_BEGIN


template <size_t WIDTH, size_t HEIGHT>
class TFigureBoard final{

public:

    using figure_ptr = std::shared_ptr<TFigure>;
    using board_type = std::array< std::array<TFigureUnit,WIDTH>,HEIGHT >;

    TFigureBoard()
    {
        clear();
    }
    ~TFigureBoard() = default;



    inline board_type getBoard() const noexcept
    {
        return m_board;
    }
    inline const sdleasygui::Point& getStartDisplayPoint() const {
        return m_startGameDisplayPoint;
    }
    inline void setStartDisplayPoint(const sdleasygui::Point &m_StartDisplayPoint) {
        TFigureBoard::m_startGameDisplayPoint = m_StartDisplayPoint;
    }
    inline const sdleasygui::t_size getblockLength() const {
        return m_gameblockLength;
    }
    inline void setblockLength(sdleasygui::t_size m_blockLength) {
        TFigureBoard::m_gameblockLength = m_blockLength;
    }

    void setGhostFigure(const figure_ptr& src, figure_ptr& dest)
    {
        dest = src->copy();
        dest->setAll(UnitType::Ghost);
        dest->setAll(sdleasygui::TColor{sdleasygui::ColorCode::silver,64});

        _eraseCoords(dest);

        std::shared_ptr<TFigure> copied(nullptr);
        while(_isValidation(dest))
        {
            copied = dest->goDown();
        }

        if(copied)
        {
            dest = copied;
            _setCoords(dest);
        }

        _setCoords(dest);
    }

    const bool _isValidation(figure_ptr destFigure) const {

        for (const auto& coord : destFigure->getCoords()) {
            if (isHit(coord))
                return false;
        }

        return true;
    }

    void _eraseCoords(const figure_ptr figure) {
        for (const auto& coord : figure->getCoords()) {
            const auto x = coord.getPoint().x;
            const auto y = coord.getPoint().y;
            UnitType unit = static_cast<UnitType>( m_board[y][x].getType() & (~coord.getType()) | UnitType::Empty );
            m_board[y][x].set(static_cast<UnitType>(unit));
        }
    }

    void _setCoords(const figure_ptr figure) {
        for (const auto& coord : figure->getCoords()) {
            const auto x = coord.getPoint().x;
            const auto y = coord.getPoint().y;
            m_board[y][x].set(coord.getColor());

            int unit =  m_board[y][x].getType() | coord.getType();
            unit &= ~UnitType::Empty;
            m_board[y][x].set(static_cast<UnitType>(unit));
        }
    }

    bool _eraseLinesIfFillLineThenCollapse()
    {
        std::set<sdleasygui::t_coord, std::greater<sdleasygui::t_coord>> collapedLines;
        for(sdleasygui::t_coord y = GAMEBOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
        {
            int x=0;
            for(; x < GAMEBOARD_WIDTH_COUNT ; ++x)
            {
                if( (m_board[y][x].getType() & UnitType ::Fill) != UnitType ::Fill)
                    break;
            }
            if(x==GAMEBOARD_WIDTH_COUNT) {
                collapedLines.insert(y);
                for(int x=0; x < GAMEBOARD_WIDTH_COUNT ; ++x)
                {
                    m_board[y][x].set(static_cast<UnitType>(UnitType::Empty));
                }
            }
        }

        if(collapedLines.empty())
            return false;

        for(sdleasygui::t_coord x=0 ; x < GAMEBOARD_WIDTH_COUNT ; ++x)
        {
            for(sdleasygui::t_coord y = GAMEBOARD_HEIGHT_COUNT-1 ; y >= 0 ; --y)
            {
                if( ( m_board[y][x].getType() & UnitType ::Fill) == UnitType ::Fill)
                {
                    const size_t removedCnt = std::count_if(collapedLines.begin(), collapedLines.end(),
                                                            [y](const auto _y){
                                                              return y < _y;
                                                            });

                    if(removedCnt>0)
                    {
                        m_board[y+removedCnt][x].set(UnitType::Fill);
                        m_board[y+removedCnt][x].set(m_board[y][x].getColor());
                        m_board[y][x].set(static_cast<UnitType>(UnitType::Empty));
                        m_board[y][x].set(sdleasygui::ColorCode::none);
                    }
                }
            }
        }

        return true;
    }

    const bool isExterior(const TFigureUnit& unit) const noexcept
    {
        return unit.getPoint().x < 0 || unit.getPoint().x >= WIDTH ||
            unit.getPoint().y < 0 || unit.getPoint().y >= HEIGHT;
    }

    inline const bool isHit(const TFigureUnit& unit) const noexcept
    {
        if(!isExterior(unit))
            return (m_board[unit.getPoint().y][unit.getPoint().x].getType() & UnitType::Fill)== UnitType::Fill;
        else
            return true;
    }

    void clear()
    {
        for (int i = 0 ; i < m_board.size() ; i++)
        {
            auto board = m_board[i];
            for (int l = 0 ; l < board.size() ; l++) {
                board[l] = TFigureUnit{sdleasygui::Point(i, l), 0, sdleasygui::ColorCode::none, UnitType::Empty};
            }
        }
    }


private:

    sdleasygui::Point m_startGameDisplayPoint;
    sdleasygui::t_size m_gameblockLength;

    board_type m_board;
};
/*
class make_redrawer {

public:
    TFigureBoard& m_board;

    make_redrawer(TFigureBoard& board)
    :m_board(board)
    {
        board._setCoords();
    }

    ~make_redrawer()
    {
        m_board._eraseCoords();
    }
};*/

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_FIGUREBOARD_H

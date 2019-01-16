//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_FIGUREBOARD_H
#define TERIS_FIGURE_CLASS_FIGUREBOARD_H

#include <array>
#include <memory>
#include <cassert>
#include <exception>
#include <mutex>

#include "TFigure.h"
#include "../Common/TProperty.h"

SDL_TETRIS_BEGIN

class TFigureBoard final{

public:

    TFigureBoard();

    using figure_ptr = std::shared_ptr<TFigure>;
    using board_type = std::array< std::array<TFigureUnit,GAMEBOARD_WIDTH_COUNT>,GAMEBOARD_HEIGHT_COUNT >;
    using nextfigure_board_type = std::array< std::array<TFigureUnit,NEXTFIGURE_BOARD_WIDTH_COUNT>,NEXTFIGURE_BOARD_HEIGHT_COUNT>;

    board_type getBoard() const
    {return m_board;}

    nextfigure_board_type getNextFigureBoard() const
    {return m_nextFigureBoard;}

    inline const TPoint& getStartDisplayPoint() const {
        return m_startGameDisplayPoint;
    }
    inline void setStartDisplayPoint(const TPoint &m_StartDisplayPoint) {
        TFigureBoard::m_startGameDisplayPoint = m_StartDisplayPoint;
    }
    inline const t_size getblockLength() const {
        return m_gameblockLength;
    }
    inline void setblockLength(t_size m_blockLength) {
        TFigureBoard::m_gameblockLength = m_blockLength;
    }
    inline const TPoint &getStartNextFigureDisplayPoint() const {
        return m_startNextFigureDisplayPoint;
    }
    inline void setStartNextFigureDisplayPoint(const TPoint &m_startNextFigureDisplayPoint) {
        TFigureBoard::m_startNextFigureDisplayPoint = m_startNextFigureDisplayPoint;
    }
    inline const t_size getNextFigureblockLength() const {
        return m_nextFigureblockLength;
    }
    inline void setNextFigureblockLength(t_size m_nextFigureblockLength) {
        TFigureBoard::m_nextFigureblockLength = m_nextFigureblockLength;
    }

    inline figure_ptr getNextFigure() const
    {return m_nextFigure;}

    void rotate();
    void goDown();
    void goLeft();
    void goRight();
    void goStraightDown();
    void eraseLine(const t_size lineNumber);
    void addLine(const t_size lineNumber);
    void eraseBottomLine(const t_size = 1);
    void addBottomLine(const t_size = 1);
    void createNextFigureRandomly();
    std::shared_ptr<TFigure> getCurrentFigure();

private:


    void _eraseCoords();
    void _setCoords();
    void _eraseNextFigureCoords();
    void _setNextFigureCoords();
    bool _eraseLinesIfFillLineThenCollapse();
    void _collapseFigures();
    const bool _isValidation(const TFigure *destFigure);

    TPoint m_startGameDisplayPoint;
    t_size m_gameblockLength;

    TPoint m_startNextFigureDisplayPoint;
    t_size m_nextFigureblockLength;
public:

private:
    figure_ptr m_currentFigure;
    figure_ptr m_nextFigure;
    board_type m_board;
    nextfigure_board_type m_nextFigureBoard;
    std::mutex m_mutex;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_FIGUREBOARD_H

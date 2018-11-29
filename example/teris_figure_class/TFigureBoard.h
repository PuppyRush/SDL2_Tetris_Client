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
#include "TProperty.h"

namespace tetris {

class TFigureBoard {

public:

    using BoardType = std::array< std::array<TFigureUnit,BOARD_WIDTH_COUNT>,BOARD_HEIGHT_COUNT >;
    
    inline TFigureUnit& operator()(const size_t y, const size_t x)
    {
        try
        {
            return m_board[y][x];
        }
        catch(std::out_of_range err)
        {
            return TFigureUnit::getDefaultUnit();
        }
    }
    
    BoardType getBoard() const
    {return m_board;}

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
    
    static std::shared_ptr<TFigureBoard> get();

private:

    TFigureBoard();
    void eraseCoords();
    void setCoords();
    bool eraseLineIfFillLinesAndThenCollapse();
    void collapseFigures();
    const bool isValidation(const TFigure* destFigure);
    
    std::shared_ptr<TFigure> m_currentFigure;
    BoardType m_board;
    std::mutex m_mutex;
};

}

#endif //TERIS_FIGURE_CLASS_FIGUREBOARD_H

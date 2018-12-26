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

    using BoardType = std::array< std::array<TFigureUnit,GAMEBOARD_WIDTH_COUNT>,GAMEBOARD_HEIGHT_COUNT >;
    
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

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_FIGUREBOARD_H

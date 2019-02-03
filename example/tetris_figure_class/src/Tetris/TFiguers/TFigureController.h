//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H
#define TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H

#include "TFigure.h"
#include "TFigureBoard.h"
#include "Common/TProperty.h"

SDL_TETRIS_BEGIN

class TFigureController final {

public:

    using figure_ptr = std::shared_ptr<TFigure>;
    using board_type = TFigureBoard<GAMEBOARD_WIDTH_COUNT,GAMEBOARD_HEIGHT_COUNT >;
    using board_ptr = std::shared_ptr<board_type>;
    using nextfigure_board_type = TFigureBoard<NEXTFIGURE_BOARD_WIDTH_COUNT ,NEXTFIGURE_BOARD_HEIGHT_COUNT>;
    using nextfigure_board_ptr = std::shared_ptr<nextfigure_board_type>;

    TFigureController();

    inline figure_ptr getNextFigure() const noexcept
    {return m_nextFigure;}

    inline std::shared_ptr<TFigure> getGhostFigure() const noexcept{
        return m_ghostFigure;
    }
    inline std::shared_ptr<TFigure> getCurrentFigure() const noexcept{
        return m_currentFigure;
    }
    board_ptr getBoard() const noexcept
    {return m_board;}

    nextfigure_board_ptr getNextFigureBoard() const noexcept
    {return m_nextFigureBoard;}

    void setGhostFigure();
    void command(const t_eventType event);
    void eraseLine(const t_size lineNumber);
    void addLine(const t_size lineNumber);
    void eraseBottomLine(const t_size = 1);
    void addBottomLine(const t_size = 1);
    void createNextFigureRandomly();

private:


    figure_ptr m_currentFigure;
    figure_ptr m_ghostFigure;
    figure_ptr m_nextFigure;
    board_ptr m_board;
    nextfigure_board_ptr m_nextFigureBoard;

    void _rotate();
    void _goDown();
    void _goLeft();
    void _goRight();
    void _goStraightDown();

};

SDL_TETRIS_END


#endif //TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H

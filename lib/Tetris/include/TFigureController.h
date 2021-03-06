//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRISMODULE_TFIGURECONTROLLER_H
#define TETRISMODULE_TFIGURECONTROLLER_H

#include "TFigureInterface.h"
#include "TFigureBoard.h"
#include "TProperty.h"

namespace tetris_module {

class TFigureController
{

public:

    using figure_ptr = std::shared_ptr<TFigureInterface>;
    using board_type = TFigureBoard<GAMEBOARD_WIDTH_COUNT, GAMEBOARD_HEIGHT_COUNT>;
    using board_ptr = std::shared_ptr<board_type>;
    using nextfigure_board_type = TFigureBoard<NEXTFIGURE_BOARD_WIDTH_COUNT, NEXTFIGURE_BOARD_HEIGHT_COUNT>;
    using nextfigure_board_ptr = std::shared_ptr<nextfigure_board_type>;

    TFigureController();

    inline figure_ptr getNextFigure() const noexcept
    { return m_nextFigure; }

    inline std::shared_ptr<TFigureInterface> getGhostFigure() const noexcept
    {
        return m_ghostFigure;
    }

    inline std::shared_ptr<TFigureInterface> getCurrentFigure() const noexcept
    {
        return m_currentFigure;
    }

    board_ptr getBoard() const noexcept
    { return m_board; }

    nextfigure_board_ptr getNextFigureBoard() const noexcept
    { return m_nextFigureBoard; }

    inline bool isGhostMode() const noexcept
    {
        return m_ghostmode;
    }

    inline void setGhostMode(bool mGhostmode) noexcept
    {
        m_ghostmode = mGhostmode;
    }

    void command(const seg::t_eventType event);

    void forceSet(const TFigureInterface* fig);

    void eraseLine(const seg::t_size lineNumber);

    void addLine(const seg::t_size lineNumber);

    void eraseBottomLine(const seg::t_size = 1);

    void addBottomLine(const seg::t_size = 1);

    void createNextFigureRandomly();

private:

    figure_ptr m_currentFigure;
    figure_ptr m_ghostFigure;
    figure_ptr m_nextFigure;
    board_ptr m_board;
    nextfigure_board_ptr m_nextFigureBoard;
    bool m_ghostmode = true;

    void _rotate(const seg::t_eventType event);

    void _goDown(const seg::t_eventType event);

    void _goLeft(const seg::t_eventType event);

    void _goRight(const seg::t_eventType event);

    void _goStraightDown(const seg::t_eventType event);

    void _set();
};

}

#endif //SDL2EASYGUI_TFIGURECONTROLLER_H

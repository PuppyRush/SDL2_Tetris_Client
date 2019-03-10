//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H
#define TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H

#include <boost/serialization/singleton.hpp>

#include "TFigure.h"
#include "TFigureBoard.h"
#include "Tetris/Common/TProperty.h"


SDL_TETRIS_BEGIN

class TFigureController : public boost::serialization::singleton<TFigureController> {

public:

    friend class boost::serialization::singleton<TFigureController>;

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

    void command(const sdleasygui::t_eventType event);
    void forceSet(const TFigure* fig);
    void eraseLine(const sdleasygui::t_size lineNumber);
    void addLine(const sdleasygui::t_size lineNumber);
    void eraseBottomLine(const sdleasygui::t_size = 1);
    void addBottomLine(const sdleasygui::t_size = 1);
    void createNextFigureRandomly();

    static std::shared_ptr<TFigureController> getInstance() {

        static auto inst = std::shared_ptr<TFigureController>
            (&boost::serialization::singleton<TFigureController>::get_mutable_instance());
        return inst;
    }

private:

    figure_ptr m_currentFigure;
    figure_ptr m_ghostFigure;
    figure_ptr m_nextFigure;
    board_ptr m_board;
    nextfigure_board_ptr m_nextFigureBoard;

    void _rotate(const sdleasygui::t_eventType event);
    void _goDown(const sdleasygui::t_eventType event);
    void _goLeft(const sdleasygui::t_eventType event);
    void _goRight(const sdleasygui::t_eventType event);
    void _goStraightDown(const sdleasygui::t_eventType event);
    void _set();
};

SDL_TETRIS_END


#endif //TETRIS_FIGURE_CLASS_TFIGURECONTROLLER_H

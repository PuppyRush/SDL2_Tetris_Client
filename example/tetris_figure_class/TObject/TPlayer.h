//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_FIGURE_CLASS_TPLAYER_H
#define TETRIS_FIGURE_CLASS_TPLAYER_H

#include "../Common/TDefine.h"
#include "../TGame/TFigureBoard.h"

SDL_TETRIS_BEGIN

class TPlayer final {
public:

    using board_ptr = std::shared_ptr<TFigureBoard>;

    TPlayer();
    virtual ~TPlayer() {}

    inline const std::string getUserName() const noexcept  { return m_name; }
    inline const bool isReady() const noexcept  { return m_isReady; }
    inline const int getOrder() const noexcept { return m_order; }
    inline const bool isSurvive() const noexcept { return m_isSurvive; }

    inline void setOrder(const int idx) noexcept { m_order = idx; }
    inline void setName(const std::string name) { m_name = name; }
    inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

    inline const TFigureBoard::nextfigure_board_type getNextFigureBoard() const {return m_board->getNextFigureBoard();}
    inline const TFigureBoard::board_type getBoard() const {return m_board->getBoard();}
    inline void setBoardLength(const t_size length) { m_board->setblockLength(length);}
    inline void setStartBoardPoint(const TPoint& point) { m_board->setStartDisplayPoint(point);}

    inline void rotate()
    { m_board->rotate ();}

    inline void goStraightDown()
    { m_board->goStraightDown ();}

    inline void goDown()
    { m_board->goDown ();}

    inline void goLeft()
    { m_board->goLeft ();}

    inline void goRight()
    { m_board->goRight ();}

private:
    int m_order;
    std::string m_name;
    TIPString m_ip;
    bool m_isReady;
    bool m_isSurvive;

    board_ptr m_board;


};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H

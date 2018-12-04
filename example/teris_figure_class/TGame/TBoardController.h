//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_BOARDCONTROLLER_H
#define TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

#include <memory>

#include "TFigureBoard.h"

namespace tetris
{

//controller as a proxy class for tetris
class BoardController {

public:
    ~BoardController(){}
    
    inline void rotate() const
    { m_board->rotate ();}

    inline void goStraightDown() const
    { m_board->goStraightDown ();}

    inline void goDown() const
    { m_board->goDown ();}
    
    inline void goLeft() const
    { m_board->goLeft ();}
    
    inline void goRight() const
    {m_board->goRight ();}
    
    inline TFigureBoard::BoardType getGameBoard() const
    {return TFigureBoard::get ()->getBoard ();}
    
    //singleton
    static auto get()
    {
      static auto ctl = std::shared_ptr<BoardController>(new BoardController());
      return ctl;
    }
    
private:
    BoardController();

    std::shared_ptr<TFigureBoard> m_board;
};

}

#endif //TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

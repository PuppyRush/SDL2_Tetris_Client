//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_BOARDCONTROLLER_H
#define TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

#include <memory>

#include "TFigureBoard.h"

namespace tetris
{

class BoardController {

public:
    ~BoardController(){}
    
    inline void rotate() { m_board->rotate ();}
    inline void goDown(){ m_board->goDown ();}
    inline void goLeft(){ m_board->goLeft ();}
    inline void goRight() {m_board->goRight ();}
    
    //singleton
    static auto get()
    {
      static auto ctl = std::shared_ptr<BoardController>(new BoardController());
      return ctl;
    }
    
private:
    BoardController(){}

    std::shared_ptr<TFigureBoard> m_board;
};

}

#endif //TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

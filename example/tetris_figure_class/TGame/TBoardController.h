//
// Created by chaed on 18. 11. 24.
//

#ifndef TERIS_FIGURE_CLASS_BOARDCONTROLLER_H
#define TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

#include <memory>

#include "../Common/TDefine.h"
#include "TFigureBoard.h"

SDL_TETRIS_BEGIN

//controller as a proxy class for tetris
class BoardController final{

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
    static  std::shared_ptr<BoardController> getInstance()
    {
      static auto ctl = std::shared_ptr<BoardController>(new BoardController());
      return ctl;
    }
    
private:
    BoardController();

    std::shared_ptr<TFigureBoard> m_board;
};

SDL_TETRIS_END

#endif //TERIS_FIGURE_CLASS_BOARDCONTROLLER_H

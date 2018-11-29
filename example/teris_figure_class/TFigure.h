#pragma once


#include <cassert>
#include <memory>
#include <deque>
#include <numeric>
#include <array>

#include "TType.h"
#include "TFigureUnit.h"

/***********************************************
*		            □ □ □ □                    *
*		            □ □ ■ □                    *
*		            □ □ □ □                    *
*		            □ □ □ □                    *
*	   	      Relatevie Coordnation		       *
*	(x-2,y-1) (x  ,y-1) (x,y-1)	 (x  ,y-1)     *
*	(x-2,y  ) (x-1,y  ) (x,y  )	 (x+1,y  )     *
*	(x-2,y+1) (x-1,y+1) (x,y+1)	 (x+1,y+1)     *
*	(x-2,y+2) (x-1,y+2) (x,y+2)	 (x+1,y+2)     *
***********************************************/

namespace tetris {


class TFigureBuilder;
class TFigure {
public:

    using FigureCoords = std::array<TFigureUnit, 4>;
    
    virtual ~TFigure();
    
    inline const TFigureType getType()
    { return m_figureType;}
    
    inline const size_t getWidth()
    { return m_width;}
    
    inline const size_t getHeight()
    { return m_height;}
    
    inline const TPoint getPoint()
    { return m_point;}
    
    inline const FigureCoords getCoords()
    { return m_relativeCoord;}
    
    std::shared_ptr<TFigure> goRight();
    std::shared_ptr<TFigure> goLeft();
    std::shared_ptr<TFigure> goDown();
    std::shared_ptr<TFigure> rotateLeft();
    std::shared_ptr<TFigure> rotateRight();
    const std::shared_ptr<TFigure> copy() const;
    
    virtual const TFigureType getRandomlyFigureType() const = 0;
    virtual void initialize() = 0;
    virtual const TFigureType getTypeBegin() const = 0;
    virtual const TFigureType getTypeEnd() const = 0;
    
    
protected:
    TFigure(const TFigureBuilder *bld);
    TFigure();

    t_size m_figureTypeCount;
    t_size m_width;
    t_size m_height;
    TPoint m_point;
    TFigureType m_figureType;
    FigureCoords m_relativeCoord;
    
private:
    
    virtual bool Validation() = 0;
    virtual const std::shared_ptr<TFigure> _copy() const = 0;
    virtual void _goRight() = 0;
    virtual void _goLeft() = 0;
    virtual void _goDown() = 0;
    virtual void _rotateLeft() = 0;
    virtual void _rotateRight() = 0;
};

}


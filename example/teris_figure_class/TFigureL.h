#pragma once


#define TETRIS_TFIGUREL
#ifdef TETRIS_TFIGUREL

#include <tuple>
#include "TType.h"
#include "TFigure.h"
#include "TFigureBuilder.h"

/***************************************************
*		  □ □ □ □	 □ □ ■ □   □ □ □ ■	 □ ■ ■ □   *
*		  □ ■ ■ ■	 □ □ ■ □   □ ■ ■ ■   □ □ ■ □   *
*		  □ ■ □ □    □ □ ■ ■   □ □ □ □   □ □ ■ □   *
*		  □ □ □ □    □ □ □ □   □ □ □ □   □ □ □ □   *
*	type  	 A		    B		  C			D	   *
*	width	 3		    2		  3			2	   *
*	height   2		    3		  2			3	   *
*												   *
***************************************************/

namespace tetris {

class TFigureBuilder;

class TFigureL : public TFigure {
public:
    
    virtual ~TFigureL();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;
    virtual const TFigureType getRandomlyFigureType() const override;
    
    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureL> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureL>(new TFigureL(bld));
        figure->initialize ();
        return figure;
    }

    
private:
    TFigureL(const TFigureBuilder *bld);
    virtual bool Validation() override;
    
    //implement pure virtual funtions.
    virtual void _goRight() override;
    virtual void _goLeft() override;
    virtual void _goDown() override;
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};



}

#endif
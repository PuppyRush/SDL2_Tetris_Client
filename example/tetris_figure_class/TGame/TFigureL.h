#pragma once


#define TETRIS_TFIGUREL
#ifdef TETRIS_TFIGUREL

#include "TFigure.h"

SDL_TETRIS_BEGIN

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

class TFigureBuilder;
class TFigureL final : public TFigure {
public:
    
    virtual ~TFigureL();
    virtual void initialize() final;
    virtual const TFigureType getTypeBegin() const final;
    virtual const TFigureType getTypeEnd() const final;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureL> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureL>(new TFigureL(bld));
        figure->initialize ();
        return figure;
    }

    TFigureL(){}

private:

    TFigureL(const TFigureBuilder *bld);
    virtual bool _validation() final;
    virtual const std::shared_ptr<TFigure> _copy() const final;
    //implement pure virtual funtions.
    virtual void _rotateLeft() final;
    virtual void _rotateRight() final;
};

SDL_TETRIS_END

#endif
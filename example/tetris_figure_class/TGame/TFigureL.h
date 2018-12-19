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
class TFigureL : public TFigure {
public:
    
    virtual ~TFigureL();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureL> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureL>(new TFigureL(bld));
        figure->initialize ();
        return figure;
    }

    TFigureL(){}

private:

    TFigureL(const TFigureBuilder *bld);
    virtual bool _validation() override;
    virtual const std::shared_ptr<TFigure> _copy() const override;
    //implement pure virtual funtions.
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};

SDL_TETRIS_END

#endif
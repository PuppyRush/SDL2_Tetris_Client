#pragma once


#define TETRIS_TFIGUREI
#ifdef TETRIS_TFIGUREI

#include "TFigure.h"

SDL_TETRIS_BEGIN

/********************************
*		  □ □ □ □	 □ □ ■ □    *
*		  ■ ■ ■ ■	 □ □ ■ □    *
*		  □ □ □ □    □ □ ■ □    *
*		  □ □ □ □    □ □ ■ □    *
*	type  	 A		    B	    *
*	width	 1		    4	    *
*	height   4		    1	    *
*								*
********************************/


class TFigureBuilder;
class TFigureI final : public TFigure {
public:

    virtual ~TFigureI();
    virtual void initialize() final;
    virtual const TFigureType getTypeBegin() const final;
    virtual const TFigureType getTypeEnd() const final;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureI> get(const TFigureBuilder *bld)
    {
        auto figure =  std::shared_ptr<TFigureI>(new TFigureI(bld));
        figure->initialize ();
        return figure;
    }

private:
    TFigureI(){}
    TFigureI(const TFigureBuilder *bld);
    virtual bool _validation() final;
    virtual const std::shared_ptr<TFigure> _copy() const final;
    virtual void _rotateLeft() final;
    virtual void _rotateRight() final;
};

SDL_TETRIS_END

#endif
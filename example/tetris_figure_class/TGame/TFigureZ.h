#pragma once


#define TETRIS_TFIGUREH
#ifdef TETRIS_TFIGUREH

#include "TFigure.h"

/********************************
*		  □ □ □ □	 □ □ ■ □    *
*		  □ □ ■ ■	 □ □ ■ ■    *
*		  □ ■ ■ □    □ □ □ ■    *
*		  □ □ □ □    □ □ □ □    *
*	type  	 A		    B	    *
*	width	 3		    2	    *
*	height   2		    3	    *
*								*
********************************/

SDL_TETRIS_BEGIN

class TFigureBuilder;
class TFigureZ : public TFigure {
public:

    virtual ~TFigureZ();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureZ> get(const TFigureBuilder *bld)
    {
        auto figure =  std::shared_ptr<TFigureZ>(new TFigureZ(bld));
        figure->initialize ();
        return figure;
    }

private:
    TFigureZ(){}
    TFigureZ(const TFigureBuilder *bld);
    virtual bool _validation() override;
    virtual const std::shared_ptr<TFigure> _copy() const override;
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};

SDL_TETRIS_END

#endif
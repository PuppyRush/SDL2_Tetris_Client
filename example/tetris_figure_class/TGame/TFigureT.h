#ifndef TETRIS_TFigureT
#define TETRIS_TFigureT

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "TFigure.h"

SDL_TETRIS_BEGIN

/***************************************************
*		  □ □ □ □	 □ □ ■ □   □ □ ■ □	 □ □ ■ □   *
*		  □ ■ ■ ■	 □ □ ■ ■   □ ■ ■ ■   □ ■ ■ □   *
*		  □ □ ■ □    □ □ ■ □   □ □ □ □   □ □ ■ □   *
*		  □ □ □ □    □ □ □ □   □ □ □ □   □ □ □ □   *
*	type  	 A		    B		  C			D	   *
*	width	 3		    2		  3			2	   *
*	height   2		    3		  2			3	   *
*												   *
***************************************************/


class TFigureBuilder;
class TFigureT final : public TFigure {
public:

    virtual ~TFigureT();
    virtual void initialize() final;
    virtual const TFigureType getTypeBegin() const final;
    virtual const TFigureType getTypeEnd() const final;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureT> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureT>(new TFigureT(bld));
        figure->initialize ();
        return figure;
    }

    TFigureT(){}

private:

    TFigureT(const TFigureBuilder *bld);
    virtual bool _validation() final;
    virtual const std::shared_ptr<TFigure> _copy() const final;
    //implement pure virtual funtions.
    virtual void _rotateLeft() final;
    virtual void _rotateRight() final;
};

SDL_TETRIS_END

#endif
#ifndef TETRIS_TFIGUREL
#define TETRIS_TFIGUREL

#if _MSC_VER >= 1200
  #pragma once
#endif

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
    virtual TFigureType getTypeBegin() const noexcept final;
    virtual TFigureType getTypeEnd() const noexcept final;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureL> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureL>(new TFigureL(bld));
        figure->initialize ();
        return figure;
    }

    TFigureL(){}

private:

    TFigureL(const TFigureBuilder *bld);
    virtual bool _validation() override final;
    virtual const std::shared_ptr<TFigure> _copy() const override final;
    //implement pure virtual funtions.
    virtual void _setFigureType(const TFigureType) override final;
};

SDL_TETRIS_END

#endif
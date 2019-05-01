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

class TFigureT final : public TFigure
{
public:

    virtual ~TFigureT();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureT> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureT>(new TFigureT(bld));
        figure->initialize();
        return figure;
    }

    TFigureT()
    {}

private:

    TFigureT(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigure> _copy() const override final;

    //implement pure virtual funtions.
    virtual void _setFigureType(const TFigureType) override final;
};

SDL_TETRIS_END

#endif
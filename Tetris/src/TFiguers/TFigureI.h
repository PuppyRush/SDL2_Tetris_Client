#ifndef TETRIS_TFIGUREI
#define TETRIS_TFIGUREI

#if _MSC_VER >= 1200
#pragma once
#endif

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

class TFigureI final : public TFigure
{
public:

    virtual ~TFigureI();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureI> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureI>(new TFigureI(bld));
        figure->initialize();
        return figure;
    }

private:
    TFigureI()
    {}

    TFigureI(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigure> _copy() const override final;

    virtual void _setFigureType(const TFigureType) override final;
};

SDL_TETRIS_END

#endif
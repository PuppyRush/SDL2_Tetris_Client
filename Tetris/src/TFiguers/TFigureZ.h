#ifndef TETRIS_TFIGUREZ_H
#define TETRIS_TFIGUREZ_H

#if _MSC_VER >= 1200
#pragma once
#endif

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

class TFigureZ final : public TFigure
{
public:

    virtual ~TFigureZ();

    virtual void initialize() final;

    virtual TFigureType getTypeBegin() const noexcept final;

    virtual TFigureType getTypeEnd() const noexcept final;

    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureZ> get(const TFigureBuilder* bld)
    {
        auto figure = std::shared_ptr<TFigureZ>(new TFigureZ(bld));
        figure->initialize();
        return figure;
    }

private:
    TFigureZ()
    {}

    TFigureZ(const TFigureBuilder* bld);

    virtual bool _validation() override final;

    virtual const std::shared_ptr<TFigure> _copy() const override final;

    virtual void _setFigureType(const TFigureType) override final;
};

SDL_TETRIS_END

#endif
#pragma once


#define TETRIS_TFIGUREO
#ifdef TETRIS_TFIGUREO

#include "TFigure.h"

SDL_TETRIS_BEGIN

/*********************
*		  □ □ □ □	 *
*		  □ ■ ■ □	 *
*		  □ ■ ■ □    *
*		  □ □ □ □    *
*	type  	 A		 *
*	width	 2		 *
*	height   2		 *
**********************/


class TFigureBuilder;
class TFigureO final : public TFigure {
public:

    virtual ~TFigureO();
    virtual void initialize() final;
    virtual const TFigureType getTypeBegin() const final;
    virtual const TFigureType getTypeEnd() const final;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureO> get(const TFigureBuilder *bld)
    {
        auto figure =  std::shared_ptr<TFigureO>(new TFigureO(bld));
        figure->initialize ();
        return figure;
    }

private:
    TFigureO(){}
    TFigureO(const TFigureBuilder *bld);
    virtual bool _validation() final;
    virtual const std::shared_ptr<TFigure> _copy() const final;
    virtual void _rotateLeft() final;
    virtual void _rotateRight() final;
};

SDL_TETRIS_END

#endif
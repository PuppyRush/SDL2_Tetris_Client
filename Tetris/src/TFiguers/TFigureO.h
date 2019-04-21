#ifndef TETRIS_TFIGUREO
#define TETRIS_TFIGUREO

#if _MSC_VER >= 1200
  #pragma once
#endif

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
    virtual TFigureType getTypeBegin() const noexcept final;
    virtual TFigureType getTypeEnd() const noexcept final;


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
    virtual bool _validation() override final;
    virtual const std::shared_ptr<TFigure> _copy() const override final;
    virtual void _setFigureType(const TFigureType) override final;
};

SDL_TETRIS_END

#endif
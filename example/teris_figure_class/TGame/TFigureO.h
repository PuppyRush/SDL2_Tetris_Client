#pragma once


#define TETRIS_TFIGUREO
#ifdef TETRIS_TFIGUREO

#include <tuple>
#include "../Common/TType.h"
#include "TFigure.h"
//#include "TFigureBuilder.h"

/*********************
*		  □ □ □ □	 *
*		  □ ■ ■ □	 *
*		  □ ■ ■ □    *
*		  □ □ □ □    *
*	type  	 A		 *
*	width	 2		 *
*	height   2		 *
**********************/

namespace tetris {

class TFigureBuilder;
class TFigureO : public TFigure {
public:

    virtual ~TFigureO();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;


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
    virtual bool _validation() override;
    virtual const std::shared_ptr<TFigure> _copy() const override;
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};

}

#endif
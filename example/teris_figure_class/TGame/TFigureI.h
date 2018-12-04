#pragma once


#define TETRIS_TFIGUREI
#ifdef TETRIS_TFIGUREI

#include <tuple>
#include "../Common/TType.h"
#include "TFigure.h"

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

namespace tetris {

class TFigureBuilder;
class TFigureI : public TFigure {
public:

    virtual ~TFigureI();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;


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
    virtual bool _validation() override;
    virtual const std::shared_ptr<TFigure> _copy() const override;
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};

}

#endif
#pragma once


#define TETRIS_TFigureT
#ifdef TETRIS_TFigureT

#include <tuple>
#include "../Common/TType.h"
#include "TFigure.h"

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

namespace tetris {

class TFigureBuilder;
class TFigureT : public TFigure {
public:

    virtual ~TFigureT();
    virtual void initialize() override;
    virtual const TFigureType getTypeBegin() const override;
    virtual const TFigureType getTypeEnd() const override;


    //hide base ctr, make object from builder
    static std::shared_ptr<TFigureT> get(const TFigureBuilder *bld) {
        auto figure =  std::shared_ptr<TFigureT>(new TFigureT(bld));
        figure->initialize ();
        return figure;
    }

    TFigureT(){}

private:

    TFigureT(const TFigureBuilder *bld);
    virtual bool _validation() override;
    virtual const std::shared_ptr<TFigure> _copy() const override;
    //implement pure virtual funtions.
    virtual void _rotateLeft() override;
    virtual void _rotateRight() override;
};



}

#endif
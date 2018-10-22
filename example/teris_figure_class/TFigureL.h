#pragma once

#include <tuple>
#include "TType.h"
#include "TFigure.h"

/***************************************************
*												   *
*			бс бр	бр	  бр	бр бр		бр бс бс	  бс бс бс	   *
*			бс бр	бр	  бр бр бс		бр бр бс	  бс бр бр	   *
*			бс бс	бр	  бс бс бс		бр бр бс	  бр бр бр	   *
*	type  	 A		    B		  C			D	   *
*	width	 2		    3		  2			3	   *
*	height   3		    2		  3			2	   *
*												   *
***************************************************/

class TFigureL : public TFigure
{
public:
	
	virtual ~TFigureL();

	//implement pure virtual funtions.
	virtual void goRight() override;
	virtual void goLeft() override;
	virtual void goDown() override;
	virtual void rotateLeft() override;
	virtual void rotateRight() override;

	//hide base ctr, make object from builder
	static TFigureL* get(const FigureBuilder& bld)
	{
		return new TFigureL(bld);
	}

	//base property
	const static t_width WIDTH;
	const static t_height HEIGHT;

private:
	TFigureL(const FigureBuilder& bld);
};

const t_width TFigureL::WIDTH = 3;
const t_height TFigureL::HEIGHT = 3;


#pragma once

#include <tuple>
#include "TType.h"
#include "TFigure.h"
#include "TFigureBuilder.h"

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

class TFigureLBuilder : public TFigureBuilder
{
public:

	TFigureLBuilder(const TPoint& point);
	virtual ~TFigureLBuilder() {}

	virtual TFigureLBuilder* color(const TColor& color) override;
	virtual TFigureLBuilder* type(const TFigureType& type) override;
	virtual TFigureLBuilder* age(const t_age& age) override;
	virtual TFigureL* build() override
	{
		return new TFigureL(this);
	}

private:
	virtual TFigureLBuilder* width(const t_width& width) override;
	virtual TFigureLBuilder* height(const t_height& height) override;
};

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
	static TFigureL* get(TFigureLBuilder& bld)
	{
		return bld.build();
	}

	//base property
	static const TFigureType MAX_FIGURE_TYPE;

private:
	TFigureL(const FigureBuilder* bld);
};


const TFigureType TFigureL::MAX_FIGURE_TYPE = TFigureType::D;
#pragma once

#include "TFigure.h"

class TFigureBuilder
{
public:

	TFigureBuilder(const TPoint& point) {}
	virtual ~TFigureBuilder() {}

	virtual TFigureBuilder* color(const TColor& color) = 0;
	virtual TFigureBuilder* type(const TFigureType& type) = 0;
	virtual TFigureBuilder* age(const t_age& age) = 0;

	virtual TFigure* build() = 0;

private:
	virtual TFigureBuilder* width(const t_width& width) = 0;
	virtual TFigureBuilder* height(const t_height& height) = 0;
};
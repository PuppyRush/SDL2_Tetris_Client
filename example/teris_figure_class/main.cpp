
#include "TFigureL.h"

int main()
{
	//make figure...
	FigureBuilder bld(TPoint(3, 5));
	bld.height = TFigureL::HEIGHT;
	bld.width = TFigureL::WIDTH;
	bld.color = TColor::green;
	TFigure* lFigure = TFigureL::get(bld);

	//control figure...
	lFigure->rotateRight();
	lFigure->goDown();
}
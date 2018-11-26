
#include "TFigureL.h"
#include "TFigureLBuilder.h"

#include "TBoardController.h"

int main()
{
    using namespace tetris;
    
    auto ctl = BoardController::get();
    
    
	//make figure...
	TFigureBuilder* bld = new TFigureLBuilder(TPoint(3, 5));
	bld->color( TColor::green);
	auto lFigure = TFigureL::get(bld);

	//control figure...
	lFigure->rotateRight();
	lFigure->goDown();
}

#include "TFigureL.h"
#include "TFigureLBuilder.h"

#include "TBoardController.h"

#include <iostream>
#include <random>
#include <functional>

#include "SDL.h"

SDL_Window * window;
SDL_Renderer * renderer;

using Rect =  SDL_Rect;

enum class embossingDir : char
{
	left  = 0x1,
	right = 0x2,
	top = 0x4,
	bottom = 0x8,
	all = left|right|top|bottom
};

enum rotateDir
{
	left_hand,
	right_hand
};

const Rect getEmbossedRect(const Rect &rect, const embossingDir dir)
{
	// Set render color to blue ( rect will be rendered in this color )
	SDL_SetRenderDrawColor( renderer, 249, 247, 11, 255 );
	
	SDL_Rect r2;
	switch(dir)
		{
	case embossingDir::top:
		r2.y = rect.y+5;
			r2.x = rect.x;
			r2.w = rect.w;
			r2.h = rect.h-5;
			break;
	case embossingDir::bottom:
		r2.x = rect.x;
			r2.y = rect.y;
			r2.w = rect.w;
			r2.h = rect.h-5;
			break;
	case embossingDir::left:
		r2.x = rect.x+5;
			r2.y = rect.y;
			r2.w = rect.w-5;
			r2.h = rect.h;
			break;
	case embossingDir::right:
		r2.x = rect.x;
			r2.y = rect.y;
			r2.w = rect.w-5;
			r2.h = rect.h;
			break;
	case embossingDir::all:
		r2.x = rect.x+5;
			r2.y = rect.y+5;
			r2.w = rect.w-10;
			r2.h = rect.h-10;
			break;
		}
	
	return r2;
}

int main()
{
    using namespace tetris;
    
    auto ctl = BoardController::get();
    
    
	//make figure...
	TFigureBuilder* bld = new TFigureLBuilder(TPoint(3, 5));
	bld->color( TColor::green)
	->type (TFigureType::A);
	auto lFigure = TFigureL::get(bld);

	//control figure...
	//lFigure->rotateRight();
	//lFigure->goDown();
	
	
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }
	
	window = SDL_CreateWindow("SDL_TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 800, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	
	bool quit=true;
	SDL_Event event;
	embossingDir dir = embossingDir::top;
	
	while (quit)
	{
		
		
		auto board = ctl->getGameBoard ();
		for(int y=0 ; y <board.size() ; y++)
		{
			const auto &row = board.at(y);
			for(int x=0 ; x < row.size() ; x++)
			{
				SDL_Point line[5];
				line[0].y = 50 + y*30;
				line[0].x = 50 + x*30;
				line[1].y = 50 + y*30;
				line[1].x = 50 + x*30 + 30;
				line[2].y = 50 + y*30 + 30;
				line[2].x = 50 + x*30 + 30;
				line[3].y = 50 + y*30 + 30;
				line[3].x = 50 + x*30;
				line[4].y = 50 + y*30;
				line[4].x = 50 + x*30;
				
				// Set render color to blue ( rect will be rendered in this color )
				SDL_SetRenderDrawColor( renderer,255,255,255, 255 );
				// Render rect
				SDL_RenderDrawLines (renderer, line,5);
				// Render the rect to the screen
				
				if(board[y][x].getType () == TFigureUnit::UnitType::Fill)
				{
					SDL_Rect rect;
					rect.y = 50 + y*30;
					rect.x = 50 + x*30;
					rect.h = 30;
					rect.w = 30;
						
					SDL_RenderFillRect (renderer,&rect);
					SDL_SetRenderDrawColor( renderer,0,80,60, 255 );
					SDL_RenderDrawRect (renderer,&rect);
				}
			}
		}
		
		SDL_RenderPresent(renderer);
		
		SDL_WaitEvent(&event);
		
		switch (event.type)
			{
		case SDL_QUIT:
			quit = true;
				break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
				{
			case SDLK_LEFT:
				ctl->goLeft ();
					break;
			case SDLK_RIGHT:
				ctl->goRight ();
					break;
			case SDLK_UP:
					break;
			case SDLK_DOWN:
				ctl->goDown ();
					break;
			case SDLK_RETURN:
				ctl->rotate ();
				break;
				}
				break;
		default:
			;
			}
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear (renderer);
	}
	
	// cleanup SDL
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}


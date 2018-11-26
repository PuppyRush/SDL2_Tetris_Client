
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

void rotateRect(Rect &rect, const rotateDir dir)
{

}

void goDown(Rect &rect)
{

}


int main(int args, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("SDL_TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    bool quit=true;
    SDL_Event event;
    embossingDir dir = embossingDir::top;
    while (quit)
    {
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
                        dir = embossingDir::left;
                        break;
                    case SDLK_RIGHT:
                        dir = embossingDir::right;
                        break;
                    case SDLK_UP:
                        dir = embossingDir::top;
                        break;
                    case SDLK_DOWN:
                        dir = embossingDir::bottom;
                        break;
                    case SDLK_RETURN:
                        dir = embossingDir::all;
                        break;
                }
                break;
            default:
                ;
        }

        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

        // Clear winow
        SDL_RenderClear( renderer );

        // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
        SDL_Rect r;
        r.x = 50;
        r.y = 50;
        r.w = 50;
        r.h = 50;

        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor( renderer,59, 46, 11, 255 );
        // Render rect
        SDL_RenderFillRect( renderer, &r );
        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        const auto r2= getEmbossedRect(r, dir);
        // Render rect
        SDL_RenderFillRect( renderer, &r2 );
        // Render the rect to the screen
        SDL_RenderPresent(renderer);

    }

    // cleanup SDL

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
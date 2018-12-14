//
// Created by chaed on 18. 11. 18.
//

#pragma  once

#include <random>
#include <functional>
#include <iostream>

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Common/TDefine.h"

#define WIDTH 600
#define HEIGHT 800

SDL_TETRIS_BEGIN

int TDisplayMain()
{

    SDL_Window * window;
    SDL_Renderer * renderer;

    using Rect =  SDL_Rect;


    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("SDL_TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int w, h; // texture width & height
    auto img = IMG_LoadTexture(renderer, "resources/background.jpg");
    SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    // I'm also scaling the texture 2x simply by setting the width and height
    SDL_Rect texr;
    texr.x = -50; texr.y = 100; texr.w = w; texr.h = h;

    SDL_Event event;

    /*while(1)
    {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        ctl->rotate();
                        break;
                    case SDLK_DOWN:
                        ctl->goDown();
                        break;
                    case SDLK_SPACE:
                        ctl->goStraightDown();
                        break;
                }
                break;
            default:;
        }

        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, img, NULL, &texr);
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(renderer);
    }*/

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

SDL_TETRIS_END
//
// Created by chaed on 18. 12. 2.
//

#ifndef TERIS_FIGURE_CLASS_TDEFINE_H
#define TERIS_FIGURE_CLASS_TDEFINE_H

#define SDL_TETRIS_BEGIN namespace tetris{
#define SDL_TETRIS_END }
#define SDL_TETRIS using namespace tetris;

//#define CONSTEXPR
#ifdef CONSTEXPR
  #define CE constexpr
#else
  #define CE
#endif

#endif //TERIS_FIGURE_CLASS_TDEFINE_H

//
// Created by chaed on 18. 12. 2.
//

#ifndef TERIS_FIGURE_CLASS_TDEFINE_H
#define TERIS_FIGURE_CLASS_TDEFINE_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#define GAMEINTERFACE  tetris
#define SDL_TETRIS_BEGIN namespace GAMEINTERFACE{
#define SDL_TETRIS_END }
#define SDL_TETRIS using namespace GAMEINTERFACE;

//#define CONSTEXPR
#ifdef CONSTEXPR
  #define CE constexpr
#else
  #define CE
#endif

#endif //TERIS_FIGURE_CLASS_TDEFINE_H

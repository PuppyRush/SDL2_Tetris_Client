//
// Created by chaed on 19. 2. 4.
//

#ifndef TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H
#define TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include  <thread>
#include  <string>
#include  <iostream>

#include  <ace/ACE.h>
#include  <ace/Select_Reactor.h>
#include  <ace/Reactor.h>
#include <ace/Init_ACE.h>
#include  <ace/OS.h>

#include  "GameInterface/Online/TClientConnector.h"
#include  "GameInterface/Online/TClientService.h"

#include "Common/THeader.h"

SDL_TETRIS_BEGIN

class TClientController final
{

};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TCLIENTCONTROLLER_H

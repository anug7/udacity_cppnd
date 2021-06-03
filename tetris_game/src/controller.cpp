#include <SDL.h>
#include <iostream>

#include "controller.h"

void Controller::HandleInput(bool &running, int &x, int &y, int &rot) const {
  SDL_Event e;
  x = 0;
  y = 0;
  rot = 0;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        rot = 1;
        break;
      case SDLK_DOWN:
        y = 1;
        break;
      case SDLK_LEFT:
        x = -1;
        break;
      case SDLK_RIGHT:
        x = 1;
        break;
      }
    }
  }
}

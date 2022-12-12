#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "breaker.h"

void Controller::ChangeDirection(Breaker &breaker, Breaker::Direction input,
                                 Breaker::Direction opposite) const {
  if (breaker.direction != opposite) breaker.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Breaker &breaker) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    }else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          ChangeDirection(breaker, Breaker::Direction::kLeft,
                          Breaker::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(breaker, Breaker::Direction::kRight,
                          Breaker::Direction::kLeft);
          break;
      }
    }
  }
}
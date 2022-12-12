#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"


class Game{
   public:
      Game(std::size_t grid_width, std::size_t grid_height);
      void Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration);
      int GetScore() const;
      int GetSize() const;

 private:
  Breaker breaker;
  std::vector<Tile> tiles;
  Ball ball;

  int score{0};

  void PlaceWall();
  void Update();
};

#endif
#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"


class Breaker : public Entity
{
   public:
    enum class Direction {kLeft, kRight };

    Breaker(Vector2f p_pos, SDL_Texture* p_tex)
        {}

    void update(double deltaTime);


    Direction direction = Direction::kRight;

    float speed{1.0f};
  
   private:
    int grid_width;
    int grid_height;
};

#endif
#include "breaker.h"
#include <cmath>
#include <iostream>


Breaker::Breaker(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{
  
}

void Breaker::update(double deltaTime) {
  
  switch (direction) {
    case Direction::kLeft:
      speed *= -1;
      break;

    case Direction::kRight:
      speed *= -1;
      break;
  }
 setPos(getPos().x + speed*deltaTime, getPos().y);
}
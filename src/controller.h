#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "breaker.h"

class Controller{
public:
  void HandleInput(bool &running, Breaker &breaker) const;

private:
  void ChangeDirection(Breaker &breaker, Breaker::Direction input,
                       Breaker::Direction opposite) const;
};

#endif
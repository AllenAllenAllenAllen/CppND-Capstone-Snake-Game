#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

class Food {
 public:
  Food(int r, int g, int b, bool blocked, int points, bool inc_speed)
   : r(r), g(g), b(b), points(points), inc_speed(inc_speed) {}
  
  int r;
  int g;
  int b;
  int points;
  bool inc_speed;
  
  SDL_Point position;
};

#endif
#ifndef SHINY_SPORK_DIRECTION_H
#define SHINY_SPORK_DIRECTION_H

#include <iostream>

enum class Direction {
  North,
  West,
  East,
  South
};

std::ostream& operator<<(std::ostream& out, const Direction& direction);

std::istream& operator>>(std::istream& in, Direction& direction);

#endif //SHINY_SPORK_DIRECTION_H

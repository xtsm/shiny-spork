#include "utility/Direction.h"

std::ostream& operator<<(std::ostream& out, const Direction& direction) {
  switch (direction) {
    case Direction::North:
      out << "North";
      break;
    case Direction::South:
      out << "South";
      break;
    case Direction::East:
      out << "East";
      break;
    case Direction::West:
      out << "West";
      break;
    default:
      break;
  }
  return out;
}


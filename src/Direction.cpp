#include "utility/Direction.h"
#include <string>

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

std::istream& operator>>(std::istream& in, Direction& direction) {
  std::string dir;
  in >> dir;

  if (dir == "NORTH") {
    direction = Direction::North;
  } else if (dir == "SOUTH") {
    direction = Direction::South;
  } else if (dir == "EAST") {
    direction = Direction::East;
  } else {
    direction = Direction::West;
  }

  return in;
}


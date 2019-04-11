#include "utility/Point.h"

std::istream& operator>>(std::istream& in, Point& point) {
  in >> point.x >> point.y;
  return in;
}

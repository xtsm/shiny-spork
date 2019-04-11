#ifndef SHINY_SPORK_POINT_H
#define SHINY_SPORK_POINT_H

#include <iostream>

struct Point {
  double x;
  double y;
};

std::istream& operator>>(std::istream& in, Point& point);

#endif //SHINY_SPORK_POINT_H

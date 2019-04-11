#ifndef SHINY_SPORK_POINT_H
#define SHINY_SPORK_POINT_H

#include <iostream>

struct Point {
  explicit Point(double x, double y);

  double Length();

  friend Point operator-(const Point& lhs, const Point& rhs);

  friend bool operator==(const Point& lhs, const Point& rhs);

  friend Point& operator+=(Point& lhs, const Point& rhs);

  friend Point& operator*=(Point& a, double alpha);

  double x;
  double y;
};

std::istream& operator>>(std::istream& in, Point& point);

#endif //SHINY_SPORK_POINT_H
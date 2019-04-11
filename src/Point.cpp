#include "utility/Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::Length() {
  return x * x + y * y;
}

Point operator-(const Point& lhs, const Point& rhs) {
  return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point& operator+=(Point& lhs, const Point& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

Point& operator*=(Point& a, double alpha) {
  a.x *= alpha;
  a.y *= alpha;
  return a;
}

std::istream& operator>>(std::istream& in, Point& point) {
  in >> point.x >> point.y;
  return in;
}


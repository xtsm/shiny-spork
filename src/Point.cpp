#include "utility/Point.h"

const double pi = 3.14159265358979323846;
const double from_radian_to_degree = 180 / pi;

Point::Point(double x, double y) : x(x), y(y) {}

double Point::Length() {
  return x * x + y * y;
}

double Point::AngleInDegree() {
  return (atan2(y, x) + pi) * from_radian_to_degree;
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


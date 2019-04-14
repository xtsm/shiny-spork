#ifndef SHINY_SPORK_MAP_H
#define SHINY_SPORK_MAP_H

#include <vector>
#include <string>
#include "utility/Direction.h"
#include "utility/Point.h"

class Tile {
 public:
  Tile();

  Tile(int x, int y, int number);

  void SetIsFree(bool is_free_now);
  bool IsFree() const;

  int GetNumber() const;
  void SetNumber(int number);

  int GetX() const;
  int GetY() const;

  bool IsPointOnTile(double x, double y) const;

  friend std::istream& operator>>(std::istream& in, Tile& tile);
  friend std::ostream& operator<<(std::ostream& out, const Tile& tile);

  bool operator==(const Tile& other) const;

 private:
  // Задаёт координаты верхнего левого угла
  Point coordinates_;
  int number_;
  bool is_free_;
};

class Map {
 public:

  explicit Map(std::vector<std::vector<Tile>> map);

  bool IsMoveAvailable(const Direction& direction, int x, int y) const;

  bool IsFree(int x, int y) const;

  void Set(int x, int y, int value);

  Tile GetTile(int x, int y) const;

  void LoadMapFromFile(const std::string& file_name);

 private:
  std::vector<std::vector<Tile>> map_;
};

#endif //SHINY_SPORK_MAP_H

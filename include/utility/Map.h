#ifndef SHINY_SPORK_MAP_H
#define SHINY_SPORK_MAP_H

#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "utility/Direction.h"
#include "utility/Point.h"

class Tile {
 public:
  Tile();

  explicit Tile(std::istream& in);

  Tile(int x, int y, int number);

  void Save(std::ostream& out);

  void SetIsFree(bool is_free_now);
  bool IsFree() const;

  int GetNumber() const;
  void SetNumber(int number);

  int GetX() const;
  int GetY() const;
  double RandomX() const;
  double RandomY() const;

  bool IsPointOnTile(double x, double y) const;

  friend std::istream& operator>>(std::istream& in, Tile& tile);
  friend std::ostream& operator<<(std::ostream& out, const Tile& tile);

  bool operator==(const Tile& other) const;

 private:
  // Задаёт координаты верхнего левого угла
  Point coordinates_;
  int number_;
  bool is_free_;
  static std::mt19937 twister;
  static std::uniform_int_distribution<int> dis;
};

class Map {
 public:

  explicit Map(std::vector<std::vector<Tile>> map);

  explicit Map(std::istream& in);

  void Save(std::ostream& out);

  bool IsMoveAvailable(const Direction& direction, int x, int y) const;

  bool IsFree(int x, int y) const;

  void SetIsFree(int x, int y, bool value);

  Tile& GetTile(int x, int y);

  void LoadMapFromFile(const std::string& file_name);

 private:
  std::vector<std::vector<Tile>> map_;
};

#endif //SHINY_SPORK_MAP_H

#include "utility/Map.h"
#include <fstream>
#include <tuple>
#include <queue>

Map::Map(std::vector<std::vector<Tile>> map) :
    map_(std::move(map)) {
  map_.resize(10);
  for (auto& row : map_) {
    row.resize(10);
  }
}

bool Map::IsMoveAvailable(const Direction& direction, int x, int y) const {
  switch (direction) {
    case Direction::North:
      return (y / 60 != 0 && map_[y / 60 - 1][x / 60].GetNumber()
          < map_[y / 60][x / 60].GetNumber());
    case Direction::East:
      return (x / 60 != (map_[0].size() - 1) && map_[y / 60][x / 60 + 1].GetNumber()
          < map_[y / 60][x / 60].GetNumber());
    case Direction::West:
      return (x / 60 != 0 && map_[y / 60][x / 60 - 1].GetNumber()
          < map_[y / 60][x / 60].GetNumber());
    case Direction::South:
      return (y / 60 != (map_.size() - 1) && map_[y / 60 + 1][x / 60].GetNumber()
          < map_[y / 60][x / 60].GetNumber());
    default:
      return false;
  }
}

bool Map::IsFree(int x, int y) const {
  return map_[y][x].IsFree();
}

void Map::LoadMapFromFile(const std::string& file_name) {
  std::ifstream reader(file_name);
  for (int i = 0; i < map_.size(); ++i) {
    for (int j = 0; j < map_[i].size(); ++j) {
      int number = 0;
      reader >> number;
      if (number == 0) {
        number = 1000;
      }
      // i -- y coordinate, j -- x coordinate
      map_[i][j] = Tile(j, i, number);
    }
  }
}

void Map::SetIsFree(int x, int y, bool value) {
  map_[y][x].SetIsFree(value);
}

Tile Map::GetTile(int x, int y) const {
  return map_[y / 60][x / 60];
}

Tile::Tile(int x, int y, int number)
    : coordinates_(x, y), number_(number), is_free_(number == 1000) {}

std::istream& operator>>(std::istream& in, Tile& tile) {
  in >> tile.coordinates_ >> tile.number_;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Tile& tile) {
  out << "Tile at position ("
      << tile.coordinates_.x << ", " << tile.coordinates_.y << ") "
      << " with number " << tile.number_;
  return out;
}

void Tile::SetIsFree(bool is_free_now) {
  is_free_ = is_free_now;
}

bool Tile::IsFree() const {
  return is_free_;
}

int Tile::GetNumber() const {
  return number_;
}

void Tile::SetNumber(int number) {
  number_ = number;
}

int Tile::GetX() const {
  return coordinates_.x;
}

int Tile::GetY() const {
  return coordinates_.y;
}

Tile::Tile() : Tile(0, 0, 0) {}

bool Tile::IsPointOnTile(double x, double y) const {
  return (x >= coordinates_.x && x <= coordinates_.x + 10) &&
      (y >= coordinates_.y && y <= coordinates_.y + 10);
}

bool Tile::operator==(const Tile& other) const {
  return (std::tie(coordinates_, number_)
      == std::tie(other.coordinates_, other.number_));
}

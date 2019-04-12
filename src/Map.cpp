#include "utility/Map.h"
#include <fstream>

Map::Map(std::vector<std::vector<int>> map) : map_(std::move(map)) {
  map_.resize(10);
  for (auto& row : map_) {
    row.resize(10);
  }
  LoadMapFromFile("assets/levels/map.txt");
}

bool Map::IsMoveAvailable(const Direction& direction, int x, int y) const {
  switch (direction) {
    case Direction::North:
      return (y / 60 != 0 && map_[y / 60 - 1][x / 60] > map_[y / 60][x / 60]);
    case Direction::East:
      return (x / 60 != (map_[0].size() - 1) && map_[y / 60][x / 60 + 1] > map_[y / 60][x / 60]);
    case Direction::West:
      return (x / 60 != 0 && map_[y / 60][x / 60 - 1] > map_[y / 60][x / 60]);
    case Direction::South:
      return (y / 60 != (map_.size() - 1) && map_[y / 60 + 1][x / 60] > map_[y / 60][x / 60]);
    default:
      return false;
  }
}

bool Map::IsFree(int x, int y) const {
  return map_[y][x] == 0;
}

void Map::Set(int x, int y, int value) {
  map_[y][x] = value;
}

void Map::LoadMapFromFile(const std::string& file_name) {
  std::ifstream reader(file_name);
  for (auto& row : map_) {
    for (int& element : row) {
      reader >> element;
      std::cerr << element << " ";
    }
    std::cerr << std::endl;
  }
}


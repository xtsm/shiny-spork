
#include <utility/Map.h>

Map::Map(std::vector<std::vector<int>>& map) : map_(std::move(map)) {}

bool Map::IsMoveAvailable(const Direction& direction, int x, int y) const {
  switch (direction) {
    case Direction::North:return (y != 0 && map_[y - 1][x] == 1);
    case Direction::East:return (x != (map_[0].size() - 1) && map_[y][x + 1] == 1);
    case Direction::West:return (x != 0 && map_[y][x - 1] == 1);
    case Direction::South:return (y != (map_.size() - 1) && map_[y + 1][x] == 1);
    default:return false;
  }
}


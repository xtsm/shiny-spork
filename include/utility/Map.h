#ifndef SHINY_SPORK_MAP_H
#define SHINY_SPORK_MAP_H

#include <vector>
#include <string>
#include "utility/Direction.h"

class Map {
 public:

  explicit Map(std::vector<std::vector<int>> map);

  bool IsMoveAvailable(const Direction& direction, int x, int y) const;

  bool IsFree(int, int) const;

  void Set(int, int, int);

  void LoadMapFromFile(const std::string& file_name);

 private:
  std::vector<std::vector<int>> map_;
};

#endif //SHINY_SPORK_MAP_H

#ifndef SHINY_SPORK_BASE_H
#define SHINY_SPORK_BASE_H

#include "entity/Entity.h"
#include "utility/Map.h"
#include "State.h"

#include <SFML/Graphics.hpp>

class Base : public Entity {
 public:
  Base(State& state, const std::string& source, int health, const Tile& top);

  Base(State& state, std::istream& in);

  void Init();

  void Save(std::ostream& out) override;

  void Load(const std::string& base_path);

  std::vector<sf::Text> GetInfo() const override;

  void Click(int i, int i1) override;

  bool IsAlive() const;

  void DecreaseHealth(int delta) override;

 private:
  Tile top_left_;
  std::string source_;
};

#endif //SHINY_SPORK_BASE_H

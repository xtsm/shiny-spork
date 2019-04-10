#ifndef SHINY_SPORK_ENEMY_H
#define SHINY_SPORK_ENEMY_H

#include "entity/Entity.h"
#include "utility/Direction.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity {
 public:
  Enemy(double health, double power, State& state, DrawPriority& priority);

  void DoMove() final;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

//  void SetTexture(const sf::Texture& texture) {}

 private:

  void DoMove(const Direction& direction);
};

#endif //SHINY_SPORK_ENEMY_H

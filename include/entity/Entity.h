#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Widget.h"

class Entity : public Widget {
 public:
  Entity(double health, double power,
      State& state, DrawPriority& priority);

  virtual void DoMove() = 0;

  void DecreaseHealth(double delta);
  void EncreaseHealth(double delta);

  void DoDamage(Entity& other_entity);

 protected:
  double health_;
  double power_;
  bool is_alive_;
};

#endif //SHINY_SPORK_ENTITY_HPP

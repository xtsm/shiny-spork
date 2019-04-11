#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Widget.h"
#include "utility/Point.h"

class Entity : public Widget {
 public:
  Entity(double health, double power, double x, double y,
         const std::shared_ptr<State>& state, const DrawPriority& priority);

  void LoadSprite(const std::string& file_name);

 protected:
  sf::Sprite sprite_;
  double health_;
  double power_;
  bool is_alive_;
  Point position_;
};

#endif //SHINY_SPORK_ENTITY_HPP

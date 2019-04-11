#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Widget.h"
#include "utility/Point.h"

class Entity : public Widget {
 public:
  Entity(State& state, const DrawPriority& priority);

  void LoadSprite(const std::string& file_name);

  virtual void SetInfo(bool value);

 protected:
  State& state_;
  sf::Sprite sprite_;
  bool is_info_;
};

#endif //SHINY_SPORK_ENTITY_HPP

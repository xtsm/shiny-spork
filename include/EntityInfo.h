#ifndef SHINY_SPORK_INFO_H
#define SHINY_SPORK_INFO_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Widget.h"

class EntityInfo : public Widget {
 public:
  EntityInfo(State& state, const sf::Sprite& image, const std::vector<sf::Text>& info);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  sf::Sprite image_of_entity_;
  std::vector<sf::Text> some_info_about_entity_;
  int amount_of_lines_;
  const int max_amount_of_lines_;
};

#endif //SHINY_SPORK_INFO_H

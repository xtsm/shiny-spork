#pragma once
#include "Widget.hpp"

class Button : public Widget {
 public:
  Button(State&, int, int, const sf::String&);
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void Click();
  void MouseIn();
  void MouseOut();
  bool PointCheck(int, int) const;
 protected:
  sf::Texture bg_sprite_tex_;
  sf::Sprite bg_sprite_;
  sf::Font font_;
  sf::Text text_;
};

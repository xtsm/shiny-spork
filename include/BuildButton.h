#ifndef INCLUDE_BUILDBUTTON_H_
#define INCLUDE_BUILDBUTTON_H_

#include "Button.h"
#include <string>

class BuildButton : public Button {
 public:
  explicit BuildButton(State&, int, int, std::string);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

  void Click(int, int) override;

 private:
  std::string tower_name_;
  std::string source_;
  sf::Sprite tower_sprite_;
  sf::Sprite icon_tower_sprite_;
  sf::Sprite coins_sprite_;
  int range_;
};

#endif  // INCLUDE_BUILDBUTTON_H_

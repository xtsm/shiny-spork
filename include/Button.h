#ifndef INCLUDE_BUTTON_H_
#define INCLUDE_BUTTON_H_
#include "Widget.h"

class Button : public Widget {
 public:
  Button(State&, int priority, int, int, const sf::String&);
  void draw(sf::RenderTarget&, sf::RenderStates) const override;
  void Click(int, int) override;
  void MouseIn(int, int) override;
  void MouseOut(int, int) override;
  bool PointCheck(int, int) const override;
  void SetDisable(bool);
 protected:
  sf::Texture bg_sprite_tex_;
  sf::Sprite bg_sprite_;
  sf::Font font_;
  sf::Text text_;
  bool disable_;
};
#endif  // INCLUDE_BUTTON_H_

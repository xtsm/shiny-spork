#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include "Widget.h"
#include <fstream>

class Projectile : public Widget {
 public:
  Projectile(State&, const DrawPriority&, int, int);
  void draw(sf::RenderTarget&, sf::RenderStates) const override;
 protected:
  // Текстуры снаряда
  sf::Texture sprite_tex_;
  sf::Sprite sprite_;
  // Урон, который нанесёт снаряд
  int damage_;
  // Цель, в которую летит снаряд
  // TODO(Nicksechko): Цель
};

#endif  // INCLUDE_PROJECTILE_H_

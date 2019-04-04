#ifndef SHINY_SPORK_CARTRIDGE_H
#define SHINY_SPORK_CARTRIDGE_H

#include "Widget.h"
#include <fstream>

class Projectile : public Widget {
 public:
  Projectile(State&, const DrawPriority&, int, int);
  void draw(sf::RenderTarget&, sf::RenderStates) const override;
 protected:
  //Текстуры снаряда
  sf::Texture sprite_tex_;
  sf::Sprite sprite_;
  //Урон, который нанесёт снаряд
  int damage_;
  //Цель, в которую летит снаряд
  //TODO
};

#endif //SHINY_SPORK_CARTRIDGE_H

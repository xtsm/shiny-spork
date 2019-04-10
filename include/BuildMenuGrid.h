#ifndef SHINY_SPORK_BUILDMENUGRID_H
#define SHINY_SPORK_BUILDMENUGRID_H

#include "Background.h"

class BuildMenuGrid : public Widget {
 public:
  explicit BuildMenuGrid(State&);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Load(const std::string&, const sf::Sprite&);

  void Click(int x, int y) override;

  void MouseIn(int x, int y) override;

  bool PointCheck(int x, int y) const override;

 private:
  bool loaded_;
  std::string source_;
  //Спрайт постройки
  sf::Sprite tower_sprite_;
};

#endif //SHINY_SPORK_BUILDMENUGRID_H
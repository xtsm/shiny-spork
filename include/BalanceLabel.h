#ifndef SHINY_SPORK_BALANCELABEL_H
#define SHINY_SPORK_BALANCELABEL_H

#include "Widget.h"

class BalanceLabel : public Widget {
 public:
  BalanceLabel(State&, int, int, int);

  BalanceLabel(State& state, std::istream& in);

  void Init();

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

  void Save(std::ostream& out);

  int GetBalance() const;

  void ChangeBalance(int delta);

 protected:
  int balance_;
  sf::Text text_;
  sf::Sprite coins_sprite_;
};

#endif //SHINY_SPORK_BALANCELABEL_H

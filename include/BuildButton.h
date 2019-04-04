#ifndef SHINY_SPORK_BUILDBUTTON_H
#define SHINY_SPORK_BUILDBUTTON_H

#include "Button.h"

class GameState;

class BuildButton : public Button {
 public:
  explicit BuildButton(GameState&, int, int);

  void Click() override;
 private:
  GameState& game_state_;
};

#endif //SHINY_SPORK_BUILDBUTTON_H

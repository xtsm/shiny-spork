#ifndef SHINY_SPORK_NEWGAMEBUTTON_HPP
#define SHINY_SPORK_NEWGAMEBUTTON_HPP

#include "Button.hpp"
#include <memory>

class NewGameButton : public Button {
 public:
  explicit NewGameButton(State&, int, int);

  void Click() override;
};

#endif //SHINY_SPORK_NEWGAMEBUTTON_HPP

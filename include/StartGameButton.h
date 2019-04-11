#ifndef SHINY_SPORK_STARTGAMEBUTTON_HPP
#define SHINY_SPORK_STARTGAMEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "State.h"

class StartGameButton : public Button {
 public:
  StartGameButton(State& state, int x, int y);

  void Click(int, int) final;
};

#endif //SHINY_SPORK_STARTGAMEBUTTON_HPP

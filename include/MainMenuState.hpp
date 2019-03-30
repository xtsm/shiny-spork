#pragma once
#include "State.hpp"
#include "Button.hpp"
#include "ExitButton.hpp"

class MainMenuState: public State {
 public:
  MainMenuState(StateManager& states);
  void Tick();
  void ProcessEvent(sf::Event &event);
 protected:
  Button new_game_button_;
  Button load_game_button_;
  Button settings_button_;
  ExitButton exit_button_;
};

#pragma once
#include "State.hpp"
#include "Button.hpp"

class MainMenuState: public State {
 public:
  MainMenuState(StateManager& states);
  void Tick();
  void ProcessEvent(sf::Event &event);
 protected:
  Button test_button_;
};

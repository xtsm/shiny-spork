#pragma once
#include "State.hpp"
#include "Button.hpp"
#include "ExitButton.hpp"
#include "NewGameButton.hpp"
#include "Background.hpp"

class MainMenuState: public State {
 public:
  explicit MainMenuState(StateManager& states);
  void Tick() override;
  void ProcessEvent(sf::Event& event) override;
 protected:
  NewGameButton new_game_button_;
  Button load_game_button_;
  Button settings_button_;
  ExitButton exit_button_;
  Background background_;
};

#ifndef INCLUDE_MAINMENUSTATE_H_
#define INCLUDE_MAINMENUSTATE_H_
#include "State.h"
#include "Button.h"
#include "ExitButton.h"
#include "NewGameButton.h"
#include "Background.h"
#include "LoadGameButton.h"

class MainMenuState: public State {
 public:
  explicit MainMenuState(StateManager& states);
  void Tick() override;
  void ProcessEvent(sf::Event& event) override;
 protected:
  NewGameButton new_game_button_;
  LoadGameButton load_game_button_;
  Button settings_button_;
  ExitButton exit_button_;
  Background background_;
};

#endif  // INCLUDE_MAINMENUSTATE_H_

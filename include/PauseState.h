#ifndef INCLUDE_PAUSESTATE_H_
#define INCLUDE_PAUSESTATE_H_

#include "State.h"
#include "Background.h"
#include "MainMenuButton.h"
#include "ExitButton.h"
#include "ContinueButton.h"

class PauseState : public State {
 public:
  explicit PauseState(StateManager& states);
  void Tick();
  void UpdateBackground(const sf::Texture& texture);
  void ProcessEvent(sf::Event& event);
 protected:
  Background background_;
  ContinueButton continue_button_;
  MainMenuButton main_menu_;
  ExitButton exit_button_;
};

#endif  // INCLUDE_PAUSESTATE_H_

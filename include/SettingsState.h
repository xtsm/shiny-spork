#ifndef SHINY_SPORK_SETTINGSSTATE_H
#define SHINY_SPORK_SETTINGSSTATE_H

#include "State.h"
#include "Button.h"
#include "ExitButton.h"
#include "NewGameButton.h"
#include "Background.h"
#include "LoadGameButton.h"
#include "SettingsButton.h"
#include "MainMenuButton.h"

class SettingsState : public State {
 public:
  explicit SettingsState(StateManager& states);

  void Tick() override;
  void ProcessEvent(sf::Event& event) override;
 protected:
  int width_, height_;
  std::shared_ptr<MainMenuButton> main_menu_button_ptr_;
  std::shared_ptr<Background> background_ptr_;
};

#endif //SHINY_SPORK_SETTINGSSTATE_H

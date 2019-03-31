#ifndef SHINY_SPORK_SETTINGSSTATE_H
#define SHINY_SPORK_SETTINGSSTATE_H

#include "State.h"
#include "Button.h"
#include "ExitButton.h"
#include "NewGameButton.h"
#include "Background.h"
#include "LoadGameButton.h"
#include "SettingsButton.h"

class SettingsState : public State {
 public:
  explicit SettingsState(StateManager& states);
  void Load(std::string file_name);

  void Tick() override;
  void ProcessEvent(sf::Event& event) override;
 protected:
  int width_, height_;
  Background background_;
};

#endif //SHINY_SPORK_SETTINGSSTATE_H

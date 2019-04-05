#ifndef INCLUDE_MAINMENUSTATE_H_
#define INCLUDE_MAINMENUSTATE_H_
#include "State.h"
#include "Button.h"
#include "ExitButton.h"
#include "NewGameButton.h"
#include "Background.h"
#include "LoadGameButton.h"
#include "SettingsButton.h"

class MainMenuState: public State {
 public:
  explicit MainMenuState(StateManager& states);
  void Tick() override;
  void ProcessEvent(sf::Event& event) override;
 protected:
  std::shared_ptr<NewGameButton> new_game_button_ptr_;
  std::shared_ptr<LoadGameButton> load_game_button_ptr_;
  std::shared_ptr<SettingsButton> settings_button_ptr_;
  std::shared_ptr<ExitButton> exit_button_ptr_;
  std::shared_ptr<Background> background_ptr_;
};

#endif  // INCLUDE_MAINMENUSTATE_H_

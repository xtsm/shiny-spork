#ifndef INCLUDE_PAUSESTATE_H_
#define INCLUDE_PAUSESTATE_H_

#include "State.h"
#include "Background.h"
#include "MainMenuButton.h"
#include "ExitButton.h"
#include "ContinueButton.h"
#include "SaveGameButton.h"
#include <memory>

class PauseState : public State {
 public:
  explicit PauseState(StateManager& states);
  void Tick() override;
  void UpdateBackground(const sf::Texture& texture);
  void ProcessEvent(sf::Event& event) override;
 protected:
  std::shared_ptr<Background> background_ptr_;
  std::shared_ptr<ContinueButton> continue_button_ptr_;
  std::shared_ptr<SaveGameButton> save_button_ptr_;
  std::shared_ptr<MainMenuButton> main_menu_ptr_;
  std::shared_ptr<ExitButton> exit_button_ptr_;
};

#endif  // INCLUDE_PAUSESTATE_H_

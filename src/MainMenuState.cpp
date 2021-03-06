#include "MainMenuState.h"
#include "Button.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& states) :
    State(states),
    new_game_button_ptr_(new NewGameButton(*this, 50, 200)),
    load_game_button_ptr_(new LoadGameButton(*this, 50, 250)),
    settings_button_ptr_(new SettingsButton(*this, 50, 300)),
    exit_button_ptr_(new ExitButton(*this, 50, 350)),
    background_ptr_(new Background(*this, 3)),
    emblem_ptr_(new Background(*this, 4)) {
  draw_queue_.insert(new_game_button_ptr_);
  draw_queue_.insert(load_game_button_ptr_);
  draw_queue_.insert(settings_button_ptr_);
  draw_queue_.insert(exit_button_ptr_);
  background_ptr_->LoadFromFile("assets/ui/main_menu.png");
  emblem_ptr_->LoadFromFile("assets/ui/emblem.png");
  emblem_ptr_->SetPosition(300, 38);
  background_ptr_->SetSize(800, 600);
  draw_queue_.insert(background_ptr_);
  draw_queue_.insert(emblem_ptr_);
}
void MainMenuState::Tick() {
  if (closed_) {
    states_.Close();
    closed_ = false;
  }
}
void MainMenuState::ProcessEvent(sf::Event&) {
}

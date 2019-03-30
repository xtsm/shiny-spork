#include "MainMenuState.hpp"
#include "Button.hpp"
#include "StateManager.hpp"

MainMenuState::MainMenuState(StateManager& states) :
    State(states),
    new_game_button_(*this, 50, 200, "New game"),
    load_game_button_(*this, 50, 250, "Load game"),
    settings_button_(*this, 50, 300, "Settings"),
    exit_button_(*this, 50, 350) {
  draw_queue_.insert(&new_game_button_);
  draw_queue_.insert(&load_game_button_);
  draw_queue_.insert(&settings_button_);
  draw_queue_.insert(&exit_button_);
}
void MainMenuState::Tick() {
  if (closed_) {
    states_.Close();
    closed_ = false;
  }
}
void MainMenuState::ProcessEvent(sf::Event&) {
}

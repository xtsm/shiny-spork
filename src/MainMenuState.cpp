#include "MainMenuState.h"
#include "Button.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& states) :
    State(states),
    new_game_button_(*this, 50, 200),
    load_game_button_(*this, 50, 250),
    settings_button_(*this, 50, 300),
    exit_button_(*this, 50, 350),
    background_(*this) {
  draw_queue_.insert(&new_game_button_);
  draw_queue_.insert(&load_game_button_);
  draw_queue_.insert(&settings_button_);
  draw_queue_.insert(&exit_button_);
  background_.LoadFromFile("assets/bg/1.png");
  background_.SetSize(800, 600);
  draw_queue_.insert(&background_);
}
void MainMenuState::Tick() {
  if (closed_) {
    states_.Close();
    closed_ = false;
  }
}
void MainMenuState::ProcessEvent(sf::Event&) {
}

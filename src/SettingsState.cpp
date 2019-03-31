#include <fstream>
#include "SettingsState.h"
#include "Button.h"
#include "StateManager.h"

SettingsState::SettingsState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    main_menu_button_(*this, 50, 350),
    background_(*this) {
  draw_queue_.insert(&main_menu_button_);
  background_.LoadFromFile("assets/bg/1.png");
  background_.SetSize(800, 600);
  draw_queue_.insert(&background_);
}

void SettingsState::Tick() {
  if (closed_) {
    states_.Close();
    closed_ = false;
  }
}
void SettingsState::ProcessEvent(sf::Event&) {
}

#include <fstream>
#include "SettingsState.h"
#include "Button.h"
#include "StateManager.h"

SettingsState::SettingsState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_(*this) {
}

void SettingsState::Load(std::string file_name) {
  std::ifstream fin(file_name);
  std::string bg_path;
  fin >> bg_path;
  background_.LoadFromFile(bg_path);
  draw_queue_.clear();
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

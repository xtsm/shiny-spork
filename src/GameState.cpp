#include "GameState.h"
#include <fstream>
#include <string>
#include "StateManager.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_(*this),
    panel_side_(*this) {
  panel_side_.LoadFromFile("assets/ui/panel_side.png");
  panel_side_.SetPosition(600, 0);
}
void GameState::Load(std::string file_name) {
  std::ifstream fin(file_name);
  std::string level_path;
  fin >> level_path;
  background_.LoadFromFile(level_path);
  draw_queue_.clear();
  draw_queue_.insert(&background_);
  draw_queue_.insert(&panel_side_);
}

void GameState::Tick() {
}

void GameState::ProcessEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::KeyReleased: {
        switch (event.key.code) {
          case sf::Keyboard::Escape: {
            states_.pause_state->UpdateBackground(render_.getTexture());
            states_.ChangeState(states_.pause_state);
            break;
          }
          default: break;
        }
        break;
    }
    default: break;
  }
}

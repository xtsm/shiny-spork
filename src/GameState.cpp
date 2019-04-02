#include "GameState.h"
#include <fstream>
#include <string>
#include "StateManager.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(600),
    height_(800),
    background_(*this),
    panel_side_(*this),
    pause_(*this, 7 * (this->height_ / 8), 7 * (this->width_ / 8)) {
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
  draw_queue_.insert(&pause_);
}

void GameState::Tick() {
}

void GameState::ProcessEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::KeyReleased: {
        switch (event.key.code) {
          case sf::Keyboard::Escape: {
            states_.pause->UpdateBackground(render_.getTexture());
            states_.ChangeState(states_.pause);
            break;
          }
          default: break;
        }
        break;
    }
    default: break;
  }
}

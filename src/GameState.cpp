#include "GameState.h"
#include <fstream>
#include <string>
#include "StateManager.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_(*this),
    panel_side_(*this),
    build_button(*this, 650, 50) {
  panel_side_.LoadFromFile("assets/ui/panel_side.png");
  panel_side_.SetPosition(600, 0);
}
void GameState::Load(const std::string& file_name) {
  std::ifstream fin(file_name);
  std::string level_path;
  fin >> level_path;
  background_.LoadFromFile(level_path);
  draw_queue_.clear();
  draw_queue_.insert(&background_);
  draw_queue_.insert(&panel_side_);
  draw_queue_.insert(&build_button);
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
void GameState::BuildMenu() {
  BuildTower("tower1.txt", 50, 50);
}
void GameState::BuildTower(std::string&& tower_path, int x, int y) {
  auto tower = new Tower(*this, std::move(tower_path), x, y);
  draw_queue_.insert(tower);
}

#include "GameState.h"
#include <fstream>
#include <string>
#include <memory>
#include "StateManager.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50)) {
  panel_side_ptr_->LoadFromFile("assets/ui/panel_side.png");
  panel_side_ptr_->SetPosition(600, 0);
}
void GameState::Load(const std::string& file_name) {
  std::ifstream fin(file_name);
  std::string level_path;
  fin >> level_path;
  background_ptr_->LoadFromFile(level_path);
  draw_queue_.clear();
  draw_queue_.insert(background_ptr_);
  draw_queue_.insert(panel_side_ptr_);
  draw_queue_.insert(build_button_ptr_);
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

void GameState::BuildTower(std::string&& tower_path, int x, int y) {
  draw_queue_.insert(std::make_shared<Tower>(*this, std::move(tower_path), x, y));
}

void GameState::BuildMenu() {
  BuildTower("tower1.txt", 50, 50);
}

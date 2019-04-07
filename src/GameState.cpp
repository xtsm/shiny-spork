#include <fstream>
#include <string>
#include <memory>
#include <UpdateTowerButton.h>
#include "StateManager.h"
#include "GameState.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50, std::string("assets/tower/1.txt"))),
    pause_button_ptr_(new PauseButton(*this, 700, 525))  {
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
  draw_queue_.insert(pause_button_ptr_);
}

void GameState::Tick() {
}
void GameState::Pause() {
  states_.pause_ptr_->UpdateBackground(render_.getTexture());
  states_.ChangeState(states_.pause_ptr_);
}
void GameState::ProcessEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::KeyReleased: {
        switch (event.key.code) {
          case sf::Keyboard::Escape: {
            Pause();
            break;
          }
          default: break;
        }
        break;
    }
    default: break;
  }
}

void GameState::BuildTower(const std::string& tower_path, int x, int y) {
  draw_queue_.insert(std::make_shared<Tower>(*this, tower_path, x, y));
}

void GameState::BuildMenu(const std::string& source) {
  BuildTower(source, 50, 50);
}

void GameState::InfoMenuForTower(Tower& tower) {
  draw_queue_.insert(std::make_shared<UpdateTowerButton>(*this, 650, 450, tower));
}

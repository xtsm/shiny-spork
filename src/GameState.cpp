#include <fstream>
#include <string>
#include <memory>
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50,
    std::string("assets/tower/1.txt"))),
    pause_button_ptr_(new PauseButton(*this, 700, 525)),
    towers_{},
    info_menu_{} {
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
  std::shared_ptr<Tower> tower(new Tower(*this, tower_path, x, y));
  towers_[tower->GetID()] = tower;
  draw_queue_.insert(tower);
}

void GameState::BuildMenu(const std::string& source) {
  BuildTower(source, 50, 50);
//  TODO(Nicksechko): Меню постройки
}

void GameState::InfoMenuForTower(long long id) {
  std::shared_ptr<Tower> tower = towers_[id];
  std::shared_ptr<UpdateTowerButton>
      update_tower_button(new UpdateTowerButton(*this, 650, 450, tower));
  std::shared_ptr<RemoveTowerButton>
      remove_tower_button(new RemoveTowerButton(*this, 650, 400, tower));
  info_menu_.emplace(update_tower_button->GetID(), update_tower_button);
  info_menu_.emplace(remove_tower_button->GetID(), remove_tower_button);
  for (auto& item : info_menu_) {
    draw_queue_.insert(item.second);
  }
//  TODO(Nicksechko): Информация о башне на боковой панели
}

void GameState::RemoveTower(const std::shared_ptr<Tower>& tower_ptr) {
  draw_queue_.erase(tower_ptr);
  towers_.erase(tower_ptr->GetID());
  RemoveInfoMenu();
}

void GameState::RemoveInfoMenu() {
  for (auto& item : info_menu_) {
    draw_queue_.erase(item.second);
  }
  info_menu_.clear();
}



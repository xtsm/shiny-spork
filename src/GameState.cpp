#include <fstream>
#include <string>
#include <memory>
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

GameState::GameState(StateManager& states) :
    State(states),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50,
                                      std::string("assets/tower/1.txt"),
                                      std::string("assets/tower/tower1.png"))),
    pause_button_ptr_(new PauseButton(*this, 700, 525)),
    build_menu_grid_ptr_(new BuildMenuGrid(*this)),
    towers_{},
    info_menu_{},
    is_free{} {
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

  for (auto& row : is_free) {
    for (bool& tile : row) {
      tile = true;
    }
  }
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
  is_free[x / 60][y / 60] = false;
  std::shared_ptr<Tower> tower(new Tower(*this, tower_path, x, y));
  towers_[tower->GetID()] = tower;
  draw_queue_.insert(tower);
}

void GameState::LoadBuildMenu(const std::string& source, const sf::Sprite& tower) {
  build_menu_grid_ptr_->Load(source, tower);
  draw_queue_.insert(build_menu_grid_ptr_);
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
  is_free[tower_ptr->GetX() / 60][tower_ptr->GetY() / 60] = true;
  draw_queue_.erase(tower_ptr);
  towers_.erase(tower_ptr->GetID());
  RemoveInfoMenu();
}

void GameState::RemoveBuildMenu() {
  draw_queue_.erase(build_menu_grid_ptr_);
}

void GameState::RemoveInfoMenu() {
  for (auto& item : info_menu_) {
    draw_queue_.erase(item.second);
  }
  info_menu_.clear();
}

bool GameState::IsFree(int x, int y) const {
  return is_free[x][y];
}

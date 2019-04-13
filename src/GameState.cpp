#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "GameState.h"
#include "utility/Point.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(600),
    height_(800),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50,
                                      std::string("assets/levels/tower1.txt"),
                                      std::string("assets/tower/tower1.png"))),
    pause_button_ptr_(new PauseButton(*this, 690, 550)),
    update_tower_button_ptr_(new UpdateTowerButton(*this, 650, 450, nullptr)),
    remove_tower_button_ptr_(new RemoveTowerButton(*this, 650, 400, nullptr)),
    start_game_button_ptr_(new StartGameButton(*this, 625, 500)),
    build_menu_grid_ptr_(new BuildMenuGrid(*this)),
    map_ptr_(new Map({})),
    info_menu_(),
    towers_{},
    projectiles_{},
    enemies_{},
    creator_of_enemies_(*this),
    is_enemies_produce_(false),
    current_delay_(1000),
    delay_(1000) {
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
  draw_queue_.insert(start_game_button_ptr_);
}

void GameState::Tick() {
  for (const auto& enemy : enemies_) {
    enemy.second->DoMove();
    draw_queue_.insert(enemy.second);
//    draw_queue_.erase(enemy.second);
  }

  --current_delay_;
  if (current_delay_ == 0) {
    is_enemies_produce_ = true;
    current_delay_ = delay_;
  }

  if (is_enemies_produce_) {
    CreateSomeEnemies(1);
    is_enemies_produce_ = false;
  }

  for (const auto& tower : towers_) {
    tower.second->Shot();
  }

  std::vector<int64_t> removed;
  for (const auto& projectile : projectiles_) {
    if (projectile.second->Pointing()) {
      removed.push_back(projectile.second->GetID());
    }
  }

  for (const auto& id : removed) {
    RemoveProjectile(id);
  }
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
        default:
          break;
      }
      break;
    }
    default:
      break;
  }
}

void GameState::BuildTower(const std::string& tower_path, int x, int y) {
  map_ptr_->Set(x / 60, y / 60, -1);
  std::shared_ptr<Tower> tower(new Tower(*this, tower_path, x, y));
  towers_[tower->GetID()] = tower;
  draw_queue_.insert(tower);
}

void GameState::LoadBuildMenu(const std::string& source, const sf::Sprite& tower) {
  build_menu_grid_ptr_->Load(source, tower);
  draw_queue_.insert(build_menu_grid_ptr_);
}

void GameState::InfoMenuForTower(int64_t id) {
  std::shared_ptr<Tower> tower = towers_[id];
  update_tower_button_ptr_->ChangeTower(tower);
  remove_tower_button_ptr_->ChangeTower(tower);
  draw_queue_.insert(update_tower_button_ptr_);
  draw_queue_.insert(remove_tower_button_ptr_);
  info_menu_ = tower;
  tower->SetInfo(true);
}

void GameState::RemoveTower(const std::shared_ptr<Tower>& tower_ptr) {
  map_ptr_->Set(tower_ptr->GetX() / 60, tower_ptr->GetY() / 60, 0);
  draw_queue_.erase(tower_ptr);
  towers_.erase(tower_ptr->GetID());
  RemoveInfoMenu();
}

void GameState::RemoveBuildMenu() {
  draw_queue_.erase(build_menu_grid_ptr_);
}

void GameState::RemoveInfoMenu() {
  if (info_menu_ != nullptr) {
    info_menu_->SetInfo(false);
  }
  draw_queue_.erase(update_tower_button_ptr_);
  draw_queue_.erase(remove_tower_button_ptr_);
  update_tower_button_ptr_->ChangeTower(nullptr);
  remove_tower_button_ptr_->ChangeTower(nullptr);
  info_menu_ = nullptr;
}

bool GameState::IsFree(int x, int y) const {
  return map_ptr_->IsFree(x, y);
}

void GameState::AddProjectile(const std::shared_ptr<Projectile>& projectile) {
  projectiles_.emplace(projectile->GetID(), projectile);
  draw_queue_.insert(projectile);
  // TODO(Nicksechko): Выстрел по цели
}

void GameState::RemoveProjectile(int64_t id) {
  draw_queue_.erase(projectiles_[id]);
  projectiles_.erase(id);
}

std::shared_ptr<Enemy> GameState::FindAim(int x, int y, int range) {
  for (const auto& enemy : enemies_) {
    Point d(enemy.second->GetX() - x, enemy.second->GetY() - y);
    if (d.Length() <= range * range) {
      return enemy.second;
    }
  }
  return nullptr;
  // TODO(Nicksechko): Поск цели
}

int64_t GameState::GetAmountOfEnemies() const {
  return enemies_.size();
}

void GameState::AddNewEnemy(double health, double speed, double x, double y,
                            const Direction& move_direction) {
  std::shared_ptr<Enemy> enemy(new Enemy(health, speed, x, y, move_direction, *this, 120));
  enemies_.emplace(enemy->GetID(), enemy);
  draw_queue_.insert(enemy);
}

void GameState::RemoveEnemyById(int64_t id) {
  if (enemies_.count(id) != 0) {
    draw_queue_.erase(enemies_[id]);
    enemies_.erase(id);
  }
}

void GameState::CreateSomeEnemies(int count) {
  SetProducing(true);
  creator_of_enemies_.CreateSomeEnemies(count);
}

void GameState::SetProducing(bool produce) {
  is_enemies_produce_ = produce;
}

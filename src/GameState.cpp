#include <fstream>
#include <string>
#include <memory>
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(600),
    height_(800),
    background_ptr_(new Background(*this)),
    panel_side_ptr_(new Background(*this)),
    build_button_ptr_(new BuildButton(*this, 650, 50,
                                      std::string("assets/tower/1.txt"),
                                      std::string("assets/tower/tower1.png"))),
    pause_button_ptr_(new PauseButton(*this, 7 * (this->height_ / 8), 7 * (this->width_ / 8))),
    update_tower_button_ptr_(new UpdateTowerButton(*this, 650, 450, nullptr)),
    remove_tower_button_ptr_(new RemoveTowerButton(*this, 650, 400, nullptr)),
    build_menu_grid_ptr_(new BuildMenuGrid(*this)),
    map_ptr_(new Map({})),
    info_menu_(),
    towers_{},
    enemies_{},
    creator_of_enemies_(*this) {
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
  creator_of_enemies_.CreateSomeEnemies(1);
  for (const auto& enemy : enemies_) {
    draw_queue_.insert(enemy.second);
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

void GameState::InfoMenu(int64_t id) {
  RemoveInfoMenu();
  if (towers_.count(id)) {
    InfoMenuForTower(towers_[id]);
    return;
  }
}

void GameState::InfoMenuForTower(const std::shared_ptr<Tower>& tower) {
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

int64_t GameState::GetAmountOfEnemies() const {
  return enemies_.size();
}

void GameState::AddNewEnemy(const Enemy& enemy) {
  enemies_.emplace(enemy.GetID(), std::make_shared<Enemy>(enemy));
}

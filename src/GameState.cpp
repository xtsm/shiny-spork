#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "GameState.h"
#include "utility/Point.h"
#include "BalanceLabel.h"

GameState::GameState(StateManager& states) :
    State(states),
    width_(600),
    height_(800),
    background_ptr_(new Background(*this, 3)),
    panel_side_ptr_(new Background(*this, 1000)),
    build_button_ptrs_(),
    pause_button_ptr_(new PauseButton(*this, 690, 550)),
    update_tower_button_ptr_(new UpdateTowerButton(*this, 600, 360, nullptr)),
    remove_tower_button_ptr_(new RemoveTowerButton(*this, 600, 410, nullptr)),
    start_game_button_ptr_(new StartGameButton(*this, 625, 500)),
    build_menu_grid_ptr_(new BuildMenuGrid(*this)),
    map_ptr_(new Map({})),
    info_(new EntityInfo(*this)),
    balance_ptr_(new BalanceLabel(*this, 0, 0, 0)),
    image_tower_ptr_(),
    towers_{},
    projectiles_{},
    enemies_{},
    base_ptr_(),
    creator_of_enemies_(*this),
    is_enemies_produce_(false),
    current_delay_(1000),
    delay_(1000),
    is_info_displayed_(false),
    level_path_(),
    level_number_(1),
    max_level_number_(2),
    amount_of_waves_for_level_(2),
    amount_of_enemies_for_wave_(1),
    timer_(0),
    is_level_end_(false),
    is_game_end_(false),
    is_game_started_(false) {
  panel_side_ptr_->LoadFromFile("assets/ui/panel_side.png");
  panel_side_ptr_->SetPosition(600, 0);
}

void GameState::SaveGame() {
  std::ofstream fout("assets/save.txt");

  fout << level_path_ << std::endl;
  fout << background_ptr_->GetLastID() << std::endl;

  map_ptr_->Save(fout);
  balance_ptr_->Save(fout);

  fout << towers_.size() << std::endl;
  for (auto& tower : towers_) {
    tower.second->Save(fout);
  }

  fout << enemies_.size() << std::endl;
  for (auto& enemy : enemies_) {
    enemy.second->Save(fout);
  }

  fout << projectiles_.size() << std::endl;
  for (auto& projectile : projectiles_) {
    projectile.second->Save(fout);
  }

  base_ptr_->Save(fout);
  creator_of_enemies_.Save(fout);

  fout << current_delay_ << std::endl;
  fout << delay_ << std::endl;
}

void GameState::LoadSave() {
  std::ifstream fin("assets/save.txt");

  std::string level_path;
  fin >> level_path;
  level_number_ = std::atoi(level_path.substr(level_path.find_last_of('/') + 1).c_str());
  Load();

  int last_id(0);
  fin >> last_id;
  background_ptr_->SetLastID(last_id);

  map_ptr_ = std::make_shared<Map>(fin);

  draw_queue_.erase(balance_ptr_);
  balance_ptr_ = std::make_shared<BalanceLabel>(*this, fin);
  draw_queue_.insert(balance_ptr_);

  int cnt(0);
  fin >> cnt;
  towers_.clear();
  while (cnt--) {
    std::shared_ptr<Tower> tower(new Tower(*this, fin));
    towers_[tower->GetID()] = tower;
    draw_queue_.insert(tower);
  }

  fin >> cnt;
  enemies_.clear();
  while (cnt--) {
    std::shared_ptr<Enemy> enemy(new Enemy(*this, fin));
    enemies_[enemy->GetID()] = enemy;
    draw_queue_.insert(enemy);
  }

  fin >> cnt;
  projectiles_.clear();
  while (cnt--) {
    std::shared_ptr<Projectile> projectile(new Projectile(*this, fin));
    if (projectile->Aimed()) {
      projectiles_[projectile->GetID()] = projectile;
      draw_queue_.insert(projectile);
    }
  }

  base_ptr_ = std::make_shared<Base>(*this, fin);
  creator_of_enemies_.LoadSave(fin);

  fin >> current_delay_;
  fin >> delay_;
}

void GameState::Load() {
  draw_queue_.clear();
  towers_.clear();
  enemies_.clear();
  projectiles_.clear();

  level_path_ = "assets/levels/" + std::to_string(level_number_);
  background_ptr_->LoadFromFile(level_path_ + "/bg.png");
  draw_queue_.insert(background_ptr_);
  draw_queue_.insert(panel_side_ptr_);
  draw_queue_.insert(info_);

  std::ifstream fin(level_path_ + "/towers.txt");
  int towers_number = 0;
  std::string tower_path;
  int x = 600, y = 20;
  int balance;
  fin >> balance;
  balance_ptr_ = std::make_shared<BalanceLabel>(*this, 600, 0, balance);
  draw_queue_.insert(balance_ptr_);
  fin >> towers_number;
  build_button_ptrs_.resize(static_cast<unsigned long long int>(towers_number));
  for (auto& build_button_ptr : build_button_ptrs_) {
    fin >> tower_path;
    build_button_ptr = std::make_shared<BuildButton>(*this, x + 1, y, tower_path);
    draw_queue_.insert(build_button_ptr);
    x += 50;
    if (x == 800) {
      x = 600;
      y += 60;
    }
  }
  creator_of_enemies_.Load(level_path_);

  map_ptr_->LoadMapFromFile(level_path_ + "/map.txt");

  fin.close();
  fin.open(level_path_ + "/base.txt");
  std::string base_path;
  int health(0);
  int base_x(0), base_y(0);
  fin >> base_path;
  fin >> health;
  fin >> base_x >> base_y;
  base_ptr_ = std::make_shared<Base>(*this, base_path, health, map_ptr_->GetTile(base_x, base_y));
  draw_queue_.insert(pause_button_ptr_);
  draw_queue_.insert(start_game_button_ptr_);
  draw_queue_.insert(base_ptr_);
}

void GameState::Tick() {
  timer_++;
  auto current_enemies = enemies_;
  for (const auto& enemy : current_enemies) {
    enemy.second->DoMove();
    draw_queue_.insert(enemy.second);
    enemy.second->Tick();
//    draw_queue_.erase(enemy.second);
  }

  if (is_game_started_) {
    --current_delay_;
    if (current_delay_ == 0) {
      is_enemies_produce_ = true;
      current_delay_ = delay_;
    }
  }

  if (is_enemies_produce_ && amount_of_waves_for_level_ > 0) {
    CreateSomeEnemies(amount_of_enemies_for_wave_);
    is_enemies_produce_ = false;
    --amount_of_waves_for_level_;
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
  int balance = balance_ptr_->GetBalance();
  for (const auto& build_button_ptr : build_button_ptrs_) {
    build_button_ptr->CheckAvailability(balance);
  }

  update_tower_button_ptr_->CheckAvailability(balance);

  if (base_ptr_->IsAlive()) {
    for (const auto& info_str : base_ptr_->GetInfo()) {
      std::cerr << info_str.getString().toAnsiString() << std::endl;
    }
    states_.Close();
    return;
  }

  if (amount_of_waves_for_level_ == 0) {
    if (IsIncrementLevelIsAvailable() && enemies_.empty()) {
      states_.change_level_ptr_->ChangeBackground(render_.getTexture());
      states_.ChangeState(states_.change_level_ptr_);
    } else {
      GameOver();
    }
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
  map_ptr_->SetIsFree(x / 60, y / 60, false);
  std::shared_ptr<Tower> tower(new Tower(*this, tower_path, x, y));
  ChangeBalance(-tower->GetCost());
  towers_[tower->GetID()] = tower;
  draw_queue_.insert(tower);
  RemoveInfoMenu();
}

void GameState::LoadBuildMenu(const std::string& source, const sf::Sprite& tower, int range) {
  build_menu_grid_ptr_->SetLoaded(true);
  build_menu_grid_ptr_->Load(source, tower, range);
  image_tower_ptr_ = std::make_shared<Tower>(*this, source, 0, 0);
  info_->ChangeEntity(image_tower_ptr_);
  draw_queue_.insert(build_menu_grid_ptr_);
}

void GameState::InfoMenuForTower(int64_t id) {
  std::shared_ptr<Tower> tower = towers_[id];
  update_tower_button_ptr_->ChangeTower(tower);
  remove_tower_button_ptr_->ChangeTower(tower);
  draw_queue_.insert(update_tower_button_ptr_);
  draw_queue_.insert(remove_tower_button_ptr_);
  info_->ChangeEntity(tower);
}

void GameState::RemoveTower(const std::shared_ptr<Tower>& tower_ptr) {
  map_ptr_->SetIsFree(tower_ptr->GetX() / 60, tower_ptr->GetY() / 60, true);
  draw_queue_.erase(tower_ptr);
  towers_.erase(tower_ptr->GetID());
  RemoveInfoMenu();
}

void GameState::RemoveBuildMenu() {
  build_menu_grid_ptr_->SetLoaded(false);
  draw_queue_.erase(build_menu_grid_ptr_);
}

void GameState::RemoveInfoMenu() {
  draw_queue_.erase(update_tower_button_ptr_);
  draw_queue_.erase(remove_tower_button_ptr_);
  update_tower_button_ptr_->ChangeTower(nullptr);
  remove_tower_button_ptr_->ChangeTower(nullptr);
  info_->Clear();
}

void GameState::SetIsFree(int x, int y, bool value) {
  map_ptr_->SetIsFree(x, y, value);
}

bool GameState::IsFree(int x, int y) const {
  return map_ptr_->IsFree(x, y);
}

void GameState::AddProjectile(const std::shared_ptr<Projectile>& projectile) {
  projectiles_.emplace(projectile->GetID(), projectile);
  draw_queue_.insert(projectile);
}

void GameState::RemoveProjectile(int64_t id) {
  draw_queue_.erase(projectiles_[id]);
  projectiles_.erase(id);
}

std::shared_ptr<Enemy> GameState::FindAim(int x, int y, int range) {
  int min_number(100'000'000);
  std::shared_ptr<Enemy> aim(nullptr);
  for (const auto& enemy : enemies_) {
    Point d(enemy.second->GetCenterX() - x, enemy.second->GetCenterY() - y);
    if (d.Length() <= range * range && enemy.second->GetTile().GetNumber() < min_number) {
      min_number = enemy.second->GetTile().GetNumber();
      aim = enemy.second;
    }
  }
  return aim;
}

std::vector<std::shared_ptr<Enemy>> GameState::GetEnemiesInRange(int x, int y, int range) {
  std::vector<std::shared_ptr<Enemy>> enemies;
  for (const auto& enemy : enemies_) {
    Point d(enemy.second->GetCenterX() - x, enemy.second->GetCenterY() - y);
    if (d.Length() <= range * range) {
      enemies.push_back(enemy.second);
    }
  }
  return enemies;
}

int64_t GameState::GetAmountOfEnemies() const {
  return enemies_.size();
}

void GameState::AddNewEnemy(const std::string& path, double x, double y,
                            const Direction& move_direction) {
  std::shared_ptr<Enemy> enemy(
      new Enemy(path, x, y,
                map_ptr_->GetTile(static_cast<int>(x) / 60, static_cast<int>(y) / 60),
                move_direction, *this));
  enemies_.emplace(enemy->GetID(), enemy);
  draw_queue_.insert(enemy);
}

void GameState::ChangeEnemyPriority(long long id, DrawPriority priority) {
  if (enemies_.count(id)) {
    std::shared_ptr<Enemy> enemy = enemies_[id];
    draw_queue_.erase(enemy);
    enemy->ChangePriority(priority);
    draw_queue_.insert(enemy);
  }
}

void GameState::RemoveEnemyById(int64_t id) {
  if (enemies_.count(id) != 0) {
    draw_queue_.erase(enemies_[id]);
    enemies_.erase(id);
    if (info_->GetEntityID() == id) {
      info_->Clear();
    }
  }
}

void GameState::CreateSomeEnemies(int count) {
  SetProducing(true);
  creator_of_enemies_.CreateSomeEnemies(count);
}

void GameState::SetProducing(bool produce) {
  is_enemies_produce_ = produce;
}

void GameState::InfoMenuForEnemy(int64_t id) {
  RemoveInfoMenu();
  std::shared_ptr<Enemy> enemy = enemies_[id];
  if (enemy->IsAlive()) {
    info_->ChangeEntity(enemy);
  }
}

int GameState::GetBalance() const {
  return balance_ptr_->GetBalance();
}

void GameState::ChangeBalance(int delta) {
  balance_ptr_->ChangeBalance(delta);
}
void GameState::InfoMenuForBase() {
  RemoveInfoMenu();
  info_->ChangeEntity(base_ptr_);
}

void GameState::IncrementLevel() {
  ++level_number_;
  draw_queue_.clear();
  Load();
  states_.ChangeState(states_.game_ptr_);
}

void GameState::GameOver() {
  states_.Close();
}

int64_t GameState::GetTime() const {
  return timer_;
}

std::shared_ptr<Enemy> GameState::GetEnemyByID(int64_t id) {
  if (!enemies_.count(id)) {
    return nullptr;
  } else {
    return enemies_[id];
  }
}

void GameState::RemoveStartButton() {
  draw_queue_.erase(start_game_button_ptr_);
}

bool GameState::IsIncrementLevelIsAvailable() const {
  return level_number_ < max_level_number_;
}

void GameState::SetAmountOfWaves(int amount) {
  amount_of_waves_for_level_ = amount > 0 ? amount : 0;
}

void GameState::SetAmountOfEnemiesPerWave(int amount) {
  amount_of_enemies_for_wave_ = amount > 0 ? amount : 0;
}

void GameState::StartGame() {
  is_game_started_ = true;
  SetProducing(true);
  RemoveStartButton();
}

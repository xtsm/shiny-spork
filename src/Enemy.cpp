#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <entity/Enemy.h>

#include "entity/Enemy.h"
#include "Widget.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"
#include "utility/Direction.h"

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Entity::draw(target, states);
  target.draw(damage_bar_, states);
  target.draw(health_bar_, states);
  if (is_mouse_in_) {
    const sf::Font& font = State::GetFontResourceManager().GetOrLoadResource(
        "assets/font/default.ttf");
    sf::Text name_of_enemy(name_, font, 10);
    name_of_enemy.setFillColor(sf::Color::Red);
    name_of_enemy.setPosition(x_, y_ - 20);
    target.draw(name_of_enemy, states);
  }
}

void Enemy::DoMove() {
  std::vector<std::pair<Point, Direction>> possible_moves =
      GetAvailableMoves(static_cast<int>(position_.x), static_cast<int>(position_.y));
  if (position_ == destination_point_) {
    if (possible_moves.empty()) {
      if (x_ >= 540 && y_ <= 180) {
        std::shared_ptr<Base> base_ptr = state_.GetStateManager().game_ptr_->GetBase();
        DoDamage(base_ptr);
        return;
      }
    } else {
      std::mt19937 generator(
          static_cast<unsigned int>(std::chrono::steady_clock::now()
              .time_since_epoch().count()));

      std::uniform_int_distribution<int> distribution_of_index(
          0, static_cast<int>(possible_moves.size() - 1));

      Point new_destination;
      Direction direction;
      std::tie(new_destination, direction) =
          possible_moves[distribution_of_index(generator)];
      destination_point_ = new_destination;
      direction_of_move_ = direction;
    }
  }
  DoMove(direction_of_move_);
//  if (state_.GetStateManager().game_ptr_->GetMap()->
//      IsMoveAvailable(direction_of_move_, static_cast<int>(position_.x), static_cast<int>(position_.y))) {
//    DoMove(direction_of_move_);
//  } else {
//    destination_point_ = position_;
//    if (!possible_moves.empty()) {
//      DoMove();
//    }
//  }
}

void Enemy::DoMove(const Direction& direction) {
  switch (direction) {
    case Direction::North:position_.y = std::max(destination_point_.y, position_.y - speed_);
      y_ = static_cast<int>(position_.y - sprite_.getGlobalBounds().height);
      break;
    case Direction::East:position_.x = std::min(destination_point_.x, position_.x + speed_);
      x_ = static_cast<int>(position_.x - sprite_.getGlobalBounds().width);
      break;
    case Direction::West:position_.x = std::max(destination_point_.x, position_.x - speed_);
      x_ = static_cast<int>(position_.x - sprite_.getGlobalBounds().width);
      break;
    case Direction::South:position_.y = std::min(destination_point_.y, position_.y + speed_);
      y_ = static_cast<int>(position_.y - sprite_.getGlobalBounds().height);
      break;
    default:break;
  }

  CheckAndChangeCoordinates();
  health_bar_.setPosition(x_, y_);
  damage_bar_.setPosition(x_, y_);
  sprite_.setPosition(static_cast<float>(x_), static_cast<float>(y_));
  ChangeCurrentSpriteRect();
  Tile tile_after_move = state_.GetStateManager().game_ptr_->
      GetMap()->GetTile(static_cast<int>(position_.x) / 60, static_cast<int>(position_.y) / 60);
  ChangeDirectionTile(tile_after_move);
}

Enemy::Enemy(const std::string& path, double x, double y,
             const Tile& current_tile, const Direction& direction,
             State& state, int priority)
    : Entity(state, DrawPriority(priority, this)),
      name_(),
      frames_(0),
      current_sprite_rect_(),
      max_delay_for_sprite_change_(10),
      delay_for_sprite_change_(max_delay_for_sprite_change_),
      current_tile_(current_tile),
      direction_of_move_(direction),
      destination_point_(),
      max_health_(0),
      health_(0),
      health_bar_(),
      damage_bar_(),
      speed_(0),
      power_(0),
      drop_(0),
      position_(),
      is_alive_(true),
      poisons_timer_(50),
      poisons_() {
  LoadSprite(path + "/sprite.png");
  std::ifstream reader(path + "/config.txt");
  getline(reader, name_);
  reader >> frames_;
  reader >> drop_;
  reader >> health_ >> speed_ >> power_;
  icon_sprite_.setPosition(650, 230);
  sprite_.setTextureRect(sf::IntRect(0, 0, sprite_.getTexture()->getSize().x,
                                     sprite_.getTexture()->getSize().y / frames_));
  position_ = Point(x, y);
  destination_point_ = position_;
  x_ = static_cast<int>(x - sprite_.getGlobalBounds().width);
  y_ = static_cast<int>(y - sprite_.getGlobalBounds().height);
  sprite_.setPosition(static_cast<float>(x_), static_cast<float>(y_));
  max_health_ = health_;
  health_bar_.setFillColor(sf::Color(0, 255, 0));
  health_bar_.setPosition(x_, y_);
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getTexture()->getSize().x, 3));
  damage_bar_.setFillColor(sf::Color(255, 0, 0));
  damage_bar_.setPosition(x_, y_);
  damage_bar_.setSize(sf::Vector2f(sprite_.getTexture()->getSize().x, 3));
}

EnemyCreator::EnemyCreator(State& state) :
    state_(state),
    spawn_points_(),
    enemy_types_() {}

void EnemyCreator::Load(const std::string& level_path) {
  LoadSpawnPointsAndDirections(level_path + "/spawn_points.txt");

  std::ifstream fin(level_path + "/enemies.txt");
  int count_of_types;
  fin >> count_of_types;
  enemy_types_.resize(static_cast<unsigned long long int>(count_of_types));
  for (auto& enemy_type : enemy_types_) {
    fin >> enemy_type;
  }
}

void EnemyCreator::LoadSpawnPointsAndDirections(const std::string& path_to_file) {
  std::ifstream reader(path_to_file);
  int x, y;
  Direction direction;
  while (reader >> x >> y) {
    reader >> direction;
    spawn_points_.emplace_back(std::make_pair(x, y), direction);
  }
  reader.close();
}

void EnemyCreator::CreateSomeEnemies(int64_t count) {
  std::mt19937 generator(
      static_cast<unsigned int>(std::chrono::steady_clock::now().
          time_since_epoch().count()));
  std::uniform_int_distribution<int64_t>
      distribution_of_points(0, spawn_points_.size() - 1);

  std::uniform_int_distribution<int> distribution_of_type(
      0, static_cast<int>(enemy_types_.size() - 1));

  for (int64_t i = 0; i < count; ++i) {
    int type = distribution_of_type(generator);
    std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();
    auto point_of_spawn_with_direction = spawn_points_[distribution_of_points(generator)];
    const Tile& spawn_tile = map->GetTile(
        point_of_spawn_with_direction.first.first,
        point_of_spawn_with_direction.first.second);
    state_.GetStateManager().
        game_ptr_->AddNewEnemy("assets/enemies/" + enemy_types_[type],
                               spawn_tile.RandomX(),
                               spawn_tile.RandomY(),
                               point_of_spawn_with_direction.second);
  }

//  std::uniform_int_distribution<int> distribution_of_type(0, 50);
//
//  for (int64_t i = 0; i < count; ++i) {
//    int type = distribution_of_type(generator);
//    EnemyType health;
//    if (type >= 0 && type < 5) {
//      health = EnemyType::VeryHigh;
//    } else if (type >= 5 && type < 15) {
//      health = EnemyType::High;
//    } else if (type >= 15 && type < 30) {
//      health = EnemyType::Middle;
//    } else {
//      health = EnemyType::Low;
//    }
//
//    auto point_of_spawn_with_direction = spawn_points_[distribution_of_points(generator)];
//    state_.GetStateManager().
//        game_ptr_->AddNewEnemy(
//        GetHealthFromType(health), GetSpeedByType(health),
//        point_of_spawn_with_direction.first.x * 60,
//        point_of_spawn_with_direction.first.y * 60,
//        point_of_spawn_with_direction.second);
//  }
}

int EnemyCreator::GetHealthFromType(const EnemyType& type) {
  switch (type) {
    case EnemyType::VeryHigh:return 1000;
    case EnemyType::High:return 500;
    case EnemyType::Middle:return 250;
    case EnemyType::Low:return 100;
    default:return 0;
  }
}

double EnemyCreator::GetSpeedByType(const EnemyType& type) {
  switch (type) {
    case EnemyType::VeryHigh:return 0.2;
    case EnemyType::High:return 0.4;
    case EnemyType::Middle:return 0.8;
    case EnemyType::Low:return 1;
    default:return 0;
  }
}

void Enemy::DoDamage(const std::shared_ptr<Entity>& other_entity) {
  other_entity->DecreaseHealth(power_);
}

std::vector<std::pair<Point, Direction>> Enemy::GetAvailableMoves(int x, int y) const {
  std::vector<std::pair<Point, Direction>> available_moves;

  std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();

  if (map->IsMoveAvailable(Direction::North, x, y)) {
    available_moves.emplace_back(Point(position_.x, map->GetTile(x / 60, y / 60 - 1).RandomY()), Direction::North);
  }

  if (map->IsMoveAvailable(Direction::West, x, y)) {
    available_moves.emplace_back(Point(map->GetTile(x / 60 - 1, y / 60).RandomX(), position_.y), Direction::West);
  }

  if (map->IsMoveAvailable(Direction::East, x, y)) {
    available_moves.emplace_back(Point(map->GetTile(x / 60 + 1, y / 60).RandomX(), position_.y), Direction::East);
  }

  if (map->IsMoveAvailable(Direction::South, x, y)) {
    available_moves.emplace_back(Point(position_.x, map->GetTile(x / 60, y / 60 + 1).RandomY()), Direction::South);
  }

  return available_moves;
}

void Enemy::ChangeDirectionTile(const Tile& new_tile) {
  current_tile_ = new_tile;
}

void Enemy::ChangeCurrentSpriteRect() {
  if (delay_for_sprite_change_ == 0) {
    int width = sprite_.getTexture()->getSize().x;
    int height = sprite_.getTexture()->getSize().y / frames_;

    current_sprite_rect_ = sf::IntRect(current_sprite_rect_.left,
                                       (current_sprite_rect_.top + height) % (height * frames_), width, height);
    sprite_.setTextureRect(current_sprite_rect_);
    icon_sprite_.setTextureRect(current_sprite_rect_);
    delay_for_sprite_change_ = max_delay_for_sprite_change_;
  } else {
    --delay_for_sprite_change_;
  }
}

void Enemy::CheckAndChangeCoordinates() {
  if (x_ >= 600) {
    x_ = 599;
  }

  if (y_ >= 600) {
    y_ = 599;
  }
}

void Enemy::Click(int x, int y) {
  Entity::Click(x, y);
  state_.GetStateManager().game_ptr_->InfoMenuForEnemy(id_);
}

std::vector<sf::Text> Enemy::GetInfo() const {
  sf::Text name_text;
  sf::Text health_text;
  sf::Text damage_text;
  InitText(name_text, 650, 200, 15, sf::Color::Red);
  InitText(health_text, 620, 300, 15);
  InitText(damage_text, 620, 320, 15);
  name_text.setString(name_);
  health_text.setString("Health: " + std::to_string(health_) + " / " + std::to_string(max_health_));
  damage_text.setString("Damage: " + std::to_string(power_));

  return std::vector<sf::Text>{name_text, health_text, damage_text};
}

bool Enemy::IsAlive() const {
  return is_alive_;
}

Tile Enemy::GetTile() const {
  return current_tile_;
}

void Enemy::DecreaseHealth(int delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }
  if (health_ == 0) {
    is_alive_ = false;
    state_.GetStateManager().game_ptr_->ChangeBalance(drop_);
    state_.GetStateManager().game_ptr_->RemoveEnemyById(GetID());
    return;
  }
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getTexture()->getSize().x, 3));
}

void Enemy::AddPoison(int poison, int poison_cnt) {
  if (poisons_.empty()) {
    poisons_timer_ = 50;
  }
  poisons_[poison] = std::max(
      poisons_[poison], poison_cnt * 50 + state_.GetStateManager().game_ptr_->GetTime());
}

void Enemy::Tick() {
  poisons_timer_--;
  if (poisons_timer_ == 0) {
    while (!poisons_.empty() &&
        poisons_.rbegin()->second < state_.GetStateManager().game_ptr_->GetTime()) {
      poisons_.erase(poisons_.rbegin()->first);
    }
    if (!poisons_.empty()) {
      DecreaseHealth(poisons_.rbegin()->first);
    }
    poisons_timer_ = 50;
  }
}



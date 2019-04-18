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
  if (clicked_) {
    sf::Font font = State::GetFontResourceManager().GetOrLoadResource(
        "assets/font/default.ttf");
    sf::Text name_of_enemy(name_, font, 20);
    const int text_position_x = 600;
    name_of_enemy.setFillColor(sf::Color::Cyan);
    name_of_enemy.setPosition(text_position_x, 150);
    std::ostringstream converter;
    converter << health_;
    sf::Text health_level(sf::String(converter.str()), font, 20);
    health_level.setFillColor(sf::Color::Blue);
    health_level.setPosition(text_position_x, 200);
    converter.clear();
    converter << std::setprecision(2) << position_.x << " " << position_.y;
    sf::Text position_of_enemy(sf::String(converter.str()), font, 20);
    position_of_enemy.setFillColor(sf::Color::Black);
    position_of_enemy.setPosition(text_position_x, 250);
    target.draw(name_of_enemy, states);
    target.draw(health_level, states);
    target.draw(position_of_enemy, states);
  }
  if (is_mouse_in_) {
    sf::Font font = State::GetFontResourceManager().GetOrLoadResource(
        "assets/font/default.ttf");
    sf::Text name_of_enemy(name_, font, 10);
    name_of_enemy.setFillColor(sf::Color::Red);
    name_of_enemy.setPosition(x_, y_ - 20);
    target.draw(name_of_enemy, states);
  }
}

void Enemy::DoMove() {
  std::vector<std::pair<Tile, Direction>> possible_moves =
      GetAvailableMoves(x_, y_);
  if (current_tile_ == destination_tile_) {
    if (possible_moves.empty()) return;

    std::mt19937 generator(
        static_cast<unsigned int>(std::chrono::steady_clock::now()
            .time_since_epoch().count()));

    std::uniform_int_distribution<int> distribution_of_index(
        0, static_cast<int>(possible_moves.size() - 1));

    auto[new_destination, direction] =
    possible_moves[distribution_of_index(generator)];
    destination_tile_ = new_destination;
    direction_of_move_ = direction;
  }

  if (state_.GetStateManager().game_ptr_->GetMap()->
      IsMoveAvailable(direction_of_move_, x_, y_)) {
    DoMove(direction_of_move_);
  } else {
    destination_tile_ = current_tile_;
    if (!possible_moves.empty()) {
      DoMove();
    }
  }
}

void Enemy::DoMove(const Direction& direction) {
  switch (direction) {
    case Direction::North:
      position_.y -= speed_;
      y_ = static_cast<int>(std::floor(position_.y + sprite_.getTextureRect().height));
      break;
    case Direction::East:
      position_.x += speed_;
      x_ = static_cast<int>(std::floor(position_.x));
      break;
    case Direction::West:
      position_.x -= speed_;
      x_ = static_cast<int>(std::floor(position_.x + sprite_.getTextureRect().width));
      break;
    case Direction::South:
      position_.y += speed_;
      y_ = static_cast<int>(std::floor(position_.y));
      break;
    default:
      break;
  }

  CheckAndChangeCoordinates();
  health_bar_.setPosition(x_, y_);
  damage_bar_.setPosition(x_, y_);
  sprite_.setPosition(static_cast<float>(position_.x), static_cast<float>(position_.y));
  ChangeCurrentSpriteRect();
  Tile tile_after_move = state_.GetStateManager().game_ptr_->
      GetMap()->GetTile(x_, y_);
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
      destination_tile_(current_tile),
      max_health_(0),
      health_(0),
      health_bar_(),
      damage_bar_(),
      speed_(0),
      power_(0),
      position_{x, y},
      is_alive_(true) {
  x_ = static_cast<int>(x);
  y_ = static_cast<int>(y);
  LoadSprite(path + "/sprite.png");
  std::ifstream reader(path + "/config.txt");
  getline(reader, name_);
  reader >> frames_;
  reader >> health_ >> speed_ >> power_;
  max_health_ = health_;
  health_bar_.setFillColor(sf::Color(0, 255, 0));
  health_bar_.setPosition(x_, y_);
  health_bar_.setSize(sf::Vector2f(static_cast<float>(health_) / max_health_ * 30, 3));
  damage_bar_.setFillColor(sf::Color(255, 0, 0));
  damage_bar_.setPosition(x_, y_);
  damage_bar_.setSize(sf::Vector2f(30, 3));
  sprite_.setPosition(static_cast<float>(x), static_cast<float>(y));
  sprite_.setTextureRect(sf::IntRect(0, 0, sprite_.getTexture()->getSize().x,
                                     sprite_.getTexture()->getSize().y / frames_));
}

EnemyCreator::EnemyCreator(State& state) : state_(state) {}

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
  Point spawn_point(0, 0);
  Direction direction;
  while (reader >> spawn_point) {
    reader >> direction;
    spawn_points_.emplace_back(spawn_point, direction);
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

    auto point_of_spawn_with_direction = spawn_points_[distribution_of_points(generator)];
    state_.GetStateManager().
        game_ptr_->AddNewEnemy("assets/enemies/" + enemy_types_[type],
                               point_of_spawn_with_direction.first.x * 60,
                               point_of_spawn_with_direction.first.y * 60,
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
    case EnemyType::VeryHigh:
      return 1000;
    case EnemyType::High:
      return 500;
    case EnemyType::Middle:
      return 250;
    case EnemyType::Low:
      return 100;
    default:
      return 0;
  }
}

double EnemyCreator::GetSpeedByType(const EnemyType& type) {
  switch (type) {
    case EnemyType::VeryHigh:
      return 0.2;
    case EnemyType::High:
      return 0.4;
    case EnemyType::Middle:
      return 0.8;
    case EnemyType::Low:
      return 1;
    default:
      return 0;
  }
}

void Enemy::DecreaseHealth(int delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }
  if (health_ == 0) {
    is_alive_ = false;
    state_.GetStateManager().game_ptr_->RemoveEnemyById(GetID());
  }
  health_bar_.setSize(sf::Vector2f(static_cast<float>(health_) / max_health_ * 30, 3));
}

void Enemy::DoDamage(Enemy& other_entity) {
  other_entity.DecreaseHealth(power_);
}

std::vector<std::pair<Tile, Direction>> Enemy::GetAvailableMoves(int x, int y) const {
  std::vector<std::pair<Tile, Direction>> available_moves;

  std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();

  if (map->IsMoveAvailable(Direction::North, x, y)) {
    available_moves.emplace_back(map->GetTile(x / 60, y / 60 - 1), Direction::North);
  }

  if (map->IsMoveAvailable(Direction::West, x, y)) {
    available_moves.emplace_back(map->GetTile(x / 60 - 1, y / 60), Direction::West);
  }

  if (map->IsMoveAvailable(Direction::East, x, y)) {
    available_moves.emplace_back(map->GetTile(x / 60 + 1, y / 60), Direction::East);
  }

  if (map->IsMoveAvailable(Direction::South, x, y)) {
    available_moves.emplace_back(map->GetTile(x / 60, y / 60 + 1), Direction::South);
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

sf::Sprite Enemy::GetSprite() const {
  return sprite_;
}

std::string Enemy::GetName() const {
  return name_;
}

int Enemy::GetHealth() const {
  return health_;
}

int Enemy::GetMaxHealth() const {
  return max_health_;
}

int Enemy::GetPower() const {
  return power_;
}

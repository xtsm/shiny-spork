#include <fstream>
#include <cmath>
#include <entity/Enemy.h>

#include "entity/Enemy.h"
#include "Widget.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"
#include "utility/Direction.h"

void Enemy::DoMove() {
  if (typeid(state_) == typeid(GameState)) {
    std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();
    switch (move_direction_) {
      case Direction::North:
        if (map->IsMoveAvailable(Direction::West, x_, y_)) {
          DoMove(Direction::West);
        } else if (map->IsMoveAvailable(Direction::East, x_, y_)) {
          DoMove(Direction::East);
        } else if (map->IsMoveAvailable(Direction::North, x_, y_)) {
          DoMove(Direction::North);
        } else if (map->IsMoveAvailable(Direction::South, x_, y_)) {
          DoMove(Direction::South);
        } else {
          std::cerr << "Moves don't available" << std::endl;
        }
        break;
      case Direction::West:
        if (map->IsMoveAvailable(Direction::North, x_, y_)) {
          DoMove(Direction::North);
        } else if (map->IsMoveAvailable(Direction::South, x_, y_)) {
          DoMove(Direction::South);
        } else if (map->IsMoveAvailable(Direction::West, x_, y_)) {
          DoMove(Direction::West);
        } else if (map->IsMoveAvailable(Direction::East, x_, y_)) {
          DoMove(Direction::East);
        } else {
          std::cerr << "Moves don't available" << std::endl;
        }
        break;
      case Direction::East:
        if (map->IsMoveAvailable(Direction::North, x_, y_)) {
          DoMove(Direction::North);
        } else if (map->IsMoveAvailable(Direction::South, x_, y_)) {
          DoMove(Direction::South);
        } else if (map->IsMoveAvailable(Direction::East, x_, y_)) {
          DoMove(Direction::East);
        } else if (map->IsMoveAvailable(Direction::West, x_, y_)) {
          DoMove(Direction::West);
        } else {
          std::cerr << "Moves don't available" << std::endl;
        }
        break;
      case Direction::South:
        if (map->IsMoveAvailable(Direction::West, x_, y_)) {
          DoMove(Direction::West);
        } else if (map->IsMoveAvailable(Direction::East, x_, y_)) {
          DoMove(Direction::East);
        } else if (map->IsMoveAvailable(Direction::South, x_, y_)) {
          DoMove(Direction::South);
        } else if (map->IsMoveAvailable(Direction::North, x_, y_)) {
          DoMove(Direction::North);
        } else {
          std::cerr << "Moves don't available" << std::endl;
        }
    }
  }
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Enemy::DoMove(const Direction& direction) {
  move_direction_ = direction;
  std::cerr << "Make move in dir " << direction << std::endl;
  switch (direction) {
    case Direction::North:
      position_.y -= speed_;
      y_ = static_cast<int>(std::floor(position_.y));
      sprite_.setTextureRect(sf::IntRect(3, 33, 27, 40));
      break;
    case Direction::East:
      position_.x += speed_;
      x_ = static_cast<int>(std::floor(position_.x));
      sprite_.setTextureRect(sf::IntRect(33, 3, 27, 40));
      break;
    case Direction::West:
      position_.x -= speed_;
      x_ = static_cast<int>(std::floor(position_.x));
      sprite_.setTextureRect(sf::IntRect(3, 63, 27, 40));
      break;
    case Direction::South:
      position_.y += speed_;
      y_ = static_cast<int>(std::floor(position_.y));
      sprite_.setTextureRect(sf::IntRect(63, 3, 27, 40));
      break;
    default:
      break;
  }

  sprite_.setPosition(static_cast<float>(position_.x), static_cast<float>(position_.y));
}

Enemy::Enemy(double health, double speed, double x, double y,
             State& state, const DrawPriority& priority)
    : Entity(state, priority),
      move_direction_(Direction::West),
      health_(health),
      speed_(speed),
      power_(0),
      position_{x, y},
      is_alive_(true) {
  LoadSprite("assets/enemies/low_enemy.png");
  x_ = static_cast<int>(x);
  y_ = static_cast<int>(y);
  sprite_.setPosition(static_cast<float>(x), static_cast<float>(y));
  sprite_.setTextureRect(sf::IntRect(5, 5, 27, 40));
}

EnemyCreator::EnemyCreator(State& state)
    : state_(state),
      spawn_points_{} {
  LoadSpawnPoints("assets/enemies/1.txt");
}

void EnemyCreator::LoadSpawnPoints(const std::string& path_to_file) {
  std::ifstream reader(path_to_file);
  Point spawn_point(0, 0);
  while (reader >> spawn_point) {
    spawn_points_.push_back(spawn_point);
  }
  reader.close();
}

void EnemyCreator::CreateSomeEnemies(int64_t count) {
//TODO(nikkita1267):
  std::mt19937 generator(1488);
  std::uniform_int_distribution<int64_t>
      distribution_of_points(0, spawn_points_.size() - 1);
  std::uniform_int_distribution<int> distribution_of_type(0, 50);

  for (int64_t i = 0; i < count; ++i) {
    int type = distribution_of_type(generator);
    EnemyHealthType health;
    if (type >= 0 && type < 5) {
      health = EnemyHealthType::VeryHigh;
    } else if (type >= 5 && type < 15) {
      health = EnemyHealthType::High;
    } else if (type >= 15 && type < 30) {
      health = EnemyHealthType::Middle;
    } else {
      health = EnemyHealthType::Low;
    }

    Point point_of_spawn = spawn_points_[distribution_of_points(generator)];

    Enemy new_enemy(GetHealthFromType(health), GetSpeedByType(health),
                    point_of_spawn.x * 60, point_of_spawn.y * 60,
                    state_, DrawPriority(120, this));
    new_enemy.SetDrawPriority(
        DrawPriority(static_cast<int>(120 + new_enemy.GetID()), this));
    state_.GetStateManager().game_ptr_->AddNewEnemy(new_enemy);
  }
}

int EnemyCreator::GetHealthFromType(const EnemyHealthType& type) {
  switch (type) {
    case EnemyHealthType::VeryHigh:
      return 1000;
    case EnemyHealthType::High:
      return 500;
    case EnemyHealthType::Middle:
      return 250;
    case EnemyHealthType::Low:
      return 100;
    default:
      return 0;
  }
}

double EnemyCreator::GetSpeedByType(const EnemyHealthType& type) {
  switch (type) {
    case EnemyHealthType::VeryHigh:
      return 0.2;
    case EnemyHealthType::High:
      return 0.4;
    case EnemyHealthType::Middle:
      return 0.8;
    case EnemyHealthType::Low:
      return 1;
    default:
      return 0;
  }
}

void Enemy::DecreaseHealth(double delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }

  std::cerr << "Hp: " << health_ << std::endl;

  if (health_ == 0) {
    is_alive_ = false;
    state_.GetStateManager().game_ptr_->RemoveEnemyById(GetID());
  }
}

void Enemy::EncreaseHealth(double delta) {
  if (is_alive_) {
    health_ += delta;
  }
}

void Enemy::DoDamage(Enemy& other_entity) {
  other_entity.DecreaseHealth(power_);
}

void Enemy::SetDrawPriority(const DrawPriority& priority) {
  priority_ = priority;
}

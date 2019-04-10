#include <entity/Enemy.h>
#include "Widget.h"
#include "State.h"
#include "GameState.h"
#include "utility/Direction.h"

void Enemy::DoMove() {
  if (typeid(state_) == typeid(GameState)) {
    std::shared_ptr<Map> map = (dynamic_cast<GameState&>(state_)).GetMap();

    if (map->IsMoveAvailable(Direction::North, x_, y_)) {
      DoMove(Direction::North);
    } else if (map->IsMoveAvailable(Direction::South, x_, y_)) {
      DoMove(Direction::South);
    } else if (map->IsMoveAvailable(Direction::East, x_, y_)) {
      DoMove(Direction::East);
    } else if (map->IsMoveAvailable(Direction::West, x_, y_)) {
      DoMove(Direction::West);
    }
  }
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*this, states);
}

void Enemy::DoMove(const Direction& direction) {
  switch (direction) {
    case Direction::North:
      --y_;
      break;
    case Direction::East:
      ++x_;
      break;
    case Direction::West:
      --x_;
      break;
    case Direction::South:
      ++y_;
      break;
    default:
      break;
  }
}

Enemy::Enemy(double health, int x, int y,
             std::shared_ptr<State>& state, DrawPriority& priority)
    : Entity(health, 0, x, y, state, priority) {}

EnemyCreator::EnemyCreator(const std::shared_ptr<State>& state)
    : state_(state) {}

DrawPriority EnemyCreator::enemy_priority_ = DrawPriority(5, this);

void EnemyCreator::LoadSpawnPoints(const std::string& path_to_file) {
  // TODO: Read from file spawn points
}

void EnemyCreator::CreateSomeEnemies(int64_t count) {
  std::mt19937 generator;
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

    static_cast<GameState&>(*state_).AddNewEnemy(
        new Enemy(GetHealthFromType(health),
                  point_of_spawn.x, point_of_spawn.y, state_, enemy_priority_));
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

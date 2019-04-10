#include <entity/Enemy.h>
#include "Widget.h"
#include "GameState.h"
#include "utility/Direction.h"

Enemy::Enemy(double health, double power,
             State& state, DrawPriority& priority)
    : Entity(health, power, state, priority) {}

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
    case Direction::North:--y_;
      break;
    case Direction::East:++x_;
      break;
    case Direction::West:--x_;
      break;
    case Direction::South:++y_;
      break;
    default: break;
  }
}

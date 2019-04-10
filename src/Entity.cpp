#include "entity/Entity.h"

void Entity::DecreaseHealth(double delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }

  if (health_ == 0) {
    is_alive_ = false;
  }
}

void Entity::EncreaseHealth(double delta) {
  if (is_alive_) {
    health_ += delta;
  }
}

void Entity::DoDamage(Entity& other_entity) {
  other_entity.DecreaseHealth(power_);
}

Entity::Entity(double health, double power, int x, int y,
               const std::shared_ptr<State>& state, DrawPriority& priority)
    : Widget(*state, priority), health_(health), power_(power), is_alive_(true),
      position_({x, y}) {}

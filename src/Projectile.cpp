#include <cmath>
#include "entity/Projectile.h"
#include "StateManager.h"

Projectile::Projectile(State& state, std::shared_ptr<Enemy> aim,
                       int x, int y, int damage, int speed) :
    Entity(state, DrawPriority(101 + y, this)),
    aim_ptr_(std::move(aim)),
    position_(x, y),
    damage_(damage),
    speed_(speed) {
  SetPosition(x, y);
}

void Projectile::Pointing() {
  Point d = Point(aim_ptr_->GetX(), aim_ptr_->GetY()) - position_;
  if (d.Length() < speed_ * speed_) {
    aim_ptr_->DecreaseHealth(damage_);
    state_.GetStateManager().game_ptr_->RemoveProjectile(id_);
    return;
  } else {
    d *= speed_ * speed_ / d.Length();
    position_ += d;
    sprite_.setRotation(d.AngleInDegree());
    sprite_.setPosition(position_.x, position_.y);
  }
}
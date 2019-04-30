#include <cmath>
#include "entity/Projectile.h"
#include "StateManager.h"

Projectile::Projectile(State& state, std::shared_ptr<Enemy> aim, int x, int y,
                       int damage, std::string source) :
    Entity(state, DrawPriority(101 + y, this)),
    aim_ptr_(std::move(aim)),
    source_(std::move(source)),
    position_(x, y),
    damage_(damage),
    speed_(0) {
  SetPosition(x, y);

  std::ifstream fin(source_ + "/description.txt");
  fin >> speed_;
  fin >> splash_;
  fin >> range_;

  LoadSprite(source_ + "/sprite.png");
}

bool Projectile::Pointing() {
  assert(aim_ptr_ != nullptr);
  Point d = Point(aim_ptr_->GetCenterX(), aim_ptr_->GetCenterY()) - position_;
  if (d.Length() < speed_ * speed_) {
    if (range_ != 0 && splash_ != 0) {
      state_.GetStateManager().game_ptr_->
          DamageSplash(static_cast<int>(aim_ptr_->GetCenterX()),
                       static_cast<int>(aim_ptr_->GetCenterY()), splash_, range_);
    }
    aim_ptr_->DecreaseHealth(damage_);
    return true;
  } else {
    d *= speed_ * speed_ / d.Length();
    position_ += d;
    sprite_.setRotation(d.AngleInDegree() + 180);
    sprite_.setPosition(position_.x, position_.y);
    return false;
  }
}
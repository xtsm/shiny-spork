#include <cmath>
#include "entity/Projectile.h"
#include "StateManager.h"

Projectile::Projectile(State& state, std::shared_ptr<Enemy> aim, int x, int y,
                       int damage, std::string source) :
    Entity(state, DrawPriority(900, this)),
    aim_ptr_(std::move(aim)),
    source_(std::move(source)),
    position_(x, y),
    damage_(damage),
    speed_(0),
    splash_(0),
    range_(0),
    poison_(0),
    poison_cnt_(0),
    freeze_(0),
    freeze_time_(0) {
  SetPosition(x, y);

  std::ifstream fin(source_ + "/description.txt");
  int cnt;
  fin >> speed_;
  fin >> cnt;

  for (int i = 0; i < cnt; i++) {
    std::string booster;
    fin >> booster;
    if (booster == "splash") {
      fin >> splash_;
    } else if (booster == "range") {
      fin >> range_;
    } else if (booster == "poison") {
      fin >> poison_ >> poison_cnt_;
    } else if (booster == "freeze") {
      fin >> freeze_ >> freeze_time_;
    } else {
      std::cerr << "Unknown Booster" << std::endl;
    }
  }
  LoadSprite(source_ + "/sprite.png");
}

bool Projectile::Pointing() {
  assert(aim_ptr_ != nullptr);
  Point d = Point(aim_ptr_->GetCenterX(), aim_ptr_->GetCenterY()) - position_;
  if (d.Length() < speed_ * speed_) {
    std::vector<std::shared_ptr<Enemy>> enemies;
    if (range_ != 0) {
      enemies = state_.GetStateManager().game_ptr_->GetEnemiesInRange(
          static_cast<int>(aim_ptr_->GetCenterX()),
          static_cast<int>(aim_ptr_->GetCenterY()),
          range_);

      if (splash_ != 0) {
        for (auto& enemy : enemies) {
          if (enemy != aim_ptr_) {
            enemy->DecreaseHealth(splash_);
          }
        }
      }

      if (freeze_ != 0) {
        for (auto& enemy : enemies) {
          enemy->AddFreeze(freeze_, freeze_time_);
        }
      }
    }
    if (poison_ != 0) {
      aim_ptr_->AddPoison(poison_, poison_cnt_);
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
#include "Projectile.h"

Projectile::Projectile(State& state, std::shared_ptr<Enemy> aim,
                       int damage, int speed, int x, int y) :
    Entity(state, DrawPriority(101 + y, this)),
    aim_ptr_(std::move(aim)),
    damage_(damage),
    speed_(speed) {
  SetPosition(x, y);
}

void Pointing() {
  //TODO(Nicksechko): Пересчёт координат при полёте
}
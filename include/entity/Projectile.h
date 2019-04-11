#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include <fstream>
#include "entity/Enemy.h"

class Projectile : public Entity {
 public:
  Projectile(State&, std::shared_ptr<Enemy>,
             int, int, int, int);

  void Pointing();

 protected:
  // Цель, в которую летит снаряд
  std::shared_ptr<Enemy> aim_ptr_;
  Point position_;
  // Урон, который нанесёт снаряд
  int damage_;
  //Скорость полёта
  int speed_;
};

#endif  // INCLUDE_PROJECTILE_H_

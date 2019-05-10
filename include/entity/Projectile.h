#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include <fstream>
#include "entity/Enemy.h"

class Projectile : public Entity {
 public:
  Projectile(State&, std::shared_ptr<Enemy>,
             int, int, int, std::string);

  void Save(std::ofstream& fout) override;

  bool Pointing();

 protected:
  // Цель, в которую летит снаряд
  std::shared_ptr<Enemy> aim_ptr_;
  //Путь к описанию снаряда
  std::string source_;
  //Позиция снаряда
  Point position_;
  // Урон, который нанесёт снаряд
  int damage_;
  //Скорость полёта
  int speed_;
  int splash_;
  int range_;
  int poison_;
  int poison_cnt_;
  int freeze_;
  int freeze_time_;
};

#endif  // INCLUDE_PROJECTILE_H_

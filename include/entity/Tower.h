#ifndef INCLUDE_TOWER_H_
#define INCLUDE_TOWER_H_

#include <iostream>
#include <string>
#include "entity/Entity.h"
#include "Widget.h"
#include "Projectile.h"

class Tower : public Entity {
 public:
  explicit Tower(State&, const std::string& source, int, int);
  void draw(sf::RenderTarget&, sf::RenderStates) const override;
  void Click(int x, int y) override;
  // Считывает данные обновления
  void Update();
  // Пытается сделать выстрел
  void Shot();
  // Проверяет можно ли обновить башню
  bool Updatable() const;
  //Проверяет вхождение врага в дальнобойность
  bool InRange(std::shared_ptr<Enemy> enemy) const;
  std::vector<sf::Text> GetInfo() const override;
  int GetCost() const;
  int GetUpdateCost() const;

 protected:
  std::string projectile_path_;
  sf::Text text_;
  //Путь к описанию башни
  std::string source_;
  // Поток из файла с описанием уровней башни
  std::ifstream fin_;
  // Количество тиков, прошедших с предыдущего выстрела
  int timer_;
  // Название башни
  std::string tower_name_;
  // Указатель на цель
  std::shared_ptr<Enemy> aim_;
  // Максимальный возможный уровель башни
  int max_level_;
  // Уровень башни
  int level_;
  // Дальнобойность
  int range_;
  sf::CircleShape range_circle_;
  // Время перезарядки
  int cooldown_;
  // Урон от снаряда
  int damage_;
  int tower_cost_;
  int update_cost_;
};

#endif  // INCLUDE_TOWER_H_

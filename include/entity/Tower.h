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
  // Инициализириует текст
  void InitText(sf::Text&, int, int);

 protected:
  std::string projectile_sprite_path_;
  // Текст и шрифт надписи над башней
  sf::Font font_;
  sf::Text text_;
  // Поток из файла с описанием уровней башни
  std::ifstream source_;
  // Количество тиков, прошедших с предыдущего выстрела
  int timer_;
  // Максимальный возможный уровель башни
  int max_level_;
  // Уровень башни
  int level_;
  sf::Text level_text_;
  // Скорострельность в формате тик/выстрел
  int speed_;
  sf::Text speed_text_;
  // Дальнобойность
  int range_;
  sf::Text range_text_;
  // Урон от снаряда
  int damage_;
  sf::Text damage_text_;
  //Скорость снаряда
  int projectile_speed_;
  sf::Text projectile_speed_text_;
};

#endif  // INCLUDE_TOWER_H_

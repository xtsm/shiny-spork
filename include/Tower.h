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
  void Click(int, int) override;
  void MouseIn(int, int) override;
  void MouseOut(int, int) override;
  bool PointCheck(int, int) const override;
  // Считывает данные обновления
  void Update();
  // Находит ближайшего врага в радиусе дальнобойности
  void Find_Aim();
  // Пытается сделать выстрел
  void Shot();
  // Проверяет можно ли обновить башню
  bool Updatable() const;
  // Инициализириует текст
  void InitText(sf::Text&, int, int);
  //Устанавливает флаг отображения информации
  void SetInfo(bool) override;

 protected:
  // Спрайт самой башни
  sf::Sprite tower_sprite_;
  sf::Sprite icon_sprite_;
  sf::Color default_sprite_color_;
  // Текст и шрифт надписи над башней
  sf::Font font_;
  sf::Text text_;
  // Флаг, указывающий находится ли указатель над башней
  bool is_mouse_in_;
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
};

#endif  // INCLUDE_TOWER_H_

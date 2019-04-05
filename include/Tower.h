#ifndef SHINY_SPORK_TOWER_H
#define SHINY_SPORK_TOWER_H

#include <iostream>
#include <string>
#include "Widget.h"
#include "Projectile.h"

class Tower : public Widget {
 public:
  explicit Tower(State&, const std::string& source, int, int);
  void draw(sf::RenderTarget&, sf::RenderStates) const override;
  void Click() override;
  void MouseIn() override;
  void MouseOut() override;
  bool PointCheck(int, int) const override;
  //Считывает данные обновления
  void Update();
  //Находит ближайшего врага в радиусе дальнобойности
  void Find_Aim();
  //Пытается сделать выстрел
  void Shot();
  //Проверяет можно ли обновить башню
  bool Updatable() const;

 protected:
  //Спрайт и текстура самой башни
  sf::Texture tower_sprite_tex_;
  sf::Sprite tower_sprite_;
  //Текст и шрифт надписи над башней
  sf::Font font_;
  sf::Text text_;
  //Флаг, указывающий находится ли указатель над башней
  bool is_mouse_in_;
  //Поток из файла с описанием уровней башни
  std::ifstream source_;
  // Уровень башни
  int level_;
  //Максимальный возможный уровель башни
  int max_level_;
  //Спрайт и текстура снаряда
  sf::Texture projectile_sprite_tex_;
  sf::Sprite projectile_sprite_;
  //Количество тиков, прошедших с предыдущего выстрела
  int timer_;
  //Скорострельность в формате тик/выстрел
  int speed_;
  //Дальнобойность
  int range_;
  //Урон от снаряда
  int damage_;
};

#endif //SHINY_SPORK_TOWER_H

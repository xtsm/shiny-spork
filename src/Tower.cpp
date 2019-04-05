//Source файл должен иметь следующий формат:
//max_level
//speed range damage tower_image_path //Характеристики первого уровня
//speed range damage tower_image_path //Характеристики второго уровня
//...................................
//speed range damage tower_image_path //Характеристики max_level уровня
#include "Tower.h"
#include <iostream>

Tower::Tower(State& state, const std::string& source, int x, int y) :
    Widget(state, DrawPriority(4, this)),
    tower_sprite_tex_(),
    tower_sprite_(),
    source_(source),
    level_(0),
    max_level_(0),
    projectile_sprite_tex_(),
    projectile_sprite_(),
    timer_(0),
    speed_(0),
    range_(0),
    damage_(0) {
  SetPosition(x, y);

  source_ >> max_level_;
  level_ = 1;
  source_ >> speed_ >> range_ >> damage_;

  std::string tower_image_path;
  source_ >> tower_image_path;
  tower_sprite_tex_.loadFromFile(tower_image_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
  tower_sprite_.move(x, y);
  //TODO[Nicksechko] Загрузка тексстуры снаряда
}
void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(tower_sprite_, states);
}

void Tower::Click() {
  std::cerr << "Tower clicked\n";
  //TODO[Nicksechko] Отображение информации о башне на панели
}

void Tower::MouseIn() {
  if (clicked_) {
    tower_sprite_.setColor(sf::Color(255, 0, 255));
  } else {
    tower_sprite_.setColor(sf::Color(200, 200, 255));
  }
  //TODO[Nicksechko] Отображение уровня башни над ней при наведении мыши
}
void Tower::MouseOut() {
  tower_sprite_.setColor(sf::Color::White);
  //TODO[Nicksechko] Удаление надписи, созданной в MouseIn
}

bool Tower::PointCheck(int x, int y) const {
  return tower_sprite_.getGlobalBounds().contains(x, y);
}

void Tower::Update() {
  level_++;
  source_ >> speed_ >> range_ >> damage_;
  std::string tower_image_path;
  source_ >> tower_image_path;
  tower_sprite_tex_.loadFromFile(tower_image_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
  //TODO[Nicksechko] Обновление текстуры снаряда
}

void Tower::Find_Aim() {
  //TODO[Nicksechko] Поск цели
}

void Tower::Shot() {
  //TODO[Nicksechko] Выстрел по цели
}
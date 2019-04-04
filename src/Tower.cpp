//Source файл должен иметь следующий формат:
//max_level
//speed range damage tower_image_path //Характеристики первого уровня
//speed range damage tower_image_path //Характеристики второго уровня
//...................................
//speed range damage tower_image_path //Характеристики max_level уровня
#include "Tower.h"
#include <iostream>

Tower::Tower(State& state, const DrawPriority& priority, std::ifstream& source, int x, int y) :
    Widget(state, priority),
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
  sf::Image tower_image;
  tower_sprite_tex_.loadFromFile(tower_image_path);
  tower_sprite_.setTexture(tower_sprite_tex_);

  tower_sprite_.move(x, y);

  //TODO
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(tower_sprite_, states);
}

void Tower::Click() {
  std::cerr << "Tower clicked\n";
  //TODO
}

void Tower::MouseIn() {
  if (clicked_) {
    tower_sprite_.setColor(sf::Color(255, 0, 255));
  } else {
    tower_sprite_.setColor(sf::Color(200, 200, 255));
  }
}

void Tower::MouseOut() {
  tower_sprite_.setColor(sf::Color::White);
}

bool Tower::PointCheck(int x, int y) const {
  return tower_sprite_.getGlobalBounds().contains(x, y);
}

void Tower::Update() {
  //TODO
}

void Tower::Find_Aim() {
  //TODO
}

void Tower::Shot() {
  //TODO
}
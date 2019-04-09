// Source файл должен иметь следующий формат:
// max_level
// speed range damage tower_image_path // Характеристики первого уровня
// speed range damage tower_image_path // Характеристики второго уровня
// ...................................
// speed range damage tower_image_path // Характеристики max_level уровня
#include "Tower.h"
#include "StateManager.h"
#include <iostream>
#include <string>

Tower::Tower(State& state, const std::string& source, int x, int y) :
    Widget(state, DrawPriority(100 + y, this)),
    tower_sprite_tex_(),
    tower_sprite_(),
    font_(),
    text_(),
    is_mouse_in_(false),
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
  tower_sprite_tex_ = State::GetTextureResourceManager()
      .GetOrLoadResource(tower_image_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
  tower_sprite_.move(x, y - 40);

  text_.setFont(font_);
  text_.setString("LVL" + std::to_string(level_));
  text_.setOutlineColor(sf::Color::White);
  text_.setCharacterSize(10);
  font_ = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");
  text_.move(x + 10, y - 40);
  // TODO(Nicksechko): Загрузка тексстуры снаряда
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(tower_sprite_, states);
  if (is_mouse_in_) {
    target.draw(text_, states);
  }
}

void Tower::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->InfoMenuForTower(id_);
  // TODO(Nicksechko): Отображение информации о башне на панели
}

void Tower::MouseIn(int, int) {
  if (clicked_) {
    tower_sprite_.setColor(sf::Color(255, 0, 255));
  } else {
    tower_sprite_.setColor(sf::Color(200, 200, 255));
  }
  is_mouse_in_ = true;
}

void Tower::MouseOut(int, int) {
  tower_sprite_.setColor(sf::Color::White);
  is_mouse_in_ = false;
}

bool Tower::PointCheck(int x, int y) const {
  return tower_sprite_.getGlobalBounds().contains(x, y);
}

void Tower::Update() {
  level_++;
  source_ >> speed_ >> range_ >> damage_;
  std::string tower_image_path;
  source_ >> tower_image_path;
  tower_sprite_tex_ = State::GetTextureResourceManager()
      .GetOrLoadResource(tower_image_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
  text_.setString("LVL" + std::to_string(level_));
  // TODO(Nicksechko): Обновление текстуры снаряда
}

void Tower::Find_Aim() {
  // TODO(Nicksechko): Поск цели
}

void Tower::Shot() {
  // TODO(Nicksechko): Выстрел по цели
}

bool Tower::Updatable() const {
  return level_ < max_level_;
}

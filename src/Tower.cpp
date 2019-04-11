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
    Entity(state, DrawPriority(100 + y, this)),
    tower_sprite_(),
    icon_sprite_(),
    default_sprite_color_(sf::Color(255, 255, 255)),
    font_(),
    text_(),
    is_mouse_in_(false),
    source_(source),
    timer_(0),
    max_level_(0),
    level_(0),
    level_text_(),
    speed_(0),
    speed_text_(),
    range_(0),
    range_text_(),
    damage_(0),
    damage_text_() {
  SetPosition(x, y);

  icon_sprite_.move(650, 200);
  tower_sprite_.move(x + 5, y - 40);

  font_ = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");

  InitText(text_, x + 10, y - 40);
  InitText(level_text_, 650, 200);
  InitText(damage_text_, 620, 300);
  InitText(speed_text_, 620, 320);
  InitText(range_text_, 620, 340);

  source_ >> max_level_;
  Update();
  // TODO(Nicksechko): Загрузка текстуры снаряда
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (is_mouse_in_) {
    target.draw(text_, states);
  }
  if (is_info_) {
    target.draw(icon_sprite_, states);
    target.draw(level_text_, states);
    target.draw(damage_text_, states);
    target.draw(speed_text_, states);
    target.draw(range_text_, states);
  }
  target.draw(tower_sprite_, states);
}

void Tower::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->InfoMenuForTower(id_);
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
  tower_sprite_.setColor(default_sprite_color_);
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

  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager()
      .GetOrLoadResource(tower_image_path);
  icon_sprite_.setTexture(tower_sprite_tex_);
  tower_sprite_.setTexture(tower_sprite_tex_);

  text_.setString("LVL " + std::to_string(level_));
  level_text_.setString("Level " + std::to_string(level_) + " / " + std::to_string(max_level_));
  damage_text_.setString("Damage: " + std::to_string(damage_));
  speed_text_.setString("Speed: " + std::to_string(speed_));
  range_text_.setString("Range: " + std::to_string(range_));
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

void Tower::InitText(sf::Text& text, int x, int y) {
  text.setFont(font_);
  text.setOutlineColor(sf::Color::White);
  text.setCharacterSize(10);
  text.move(x, y);
}

void Tower::SetInfo(bool value) {
  if (value) {
    default_sprite_color_ = sf::Color(200, 200, 255);
    tower_sprite_.setColor(default_sprite_color_);
  } else {
    default_sprite_color_ = sf::Color(255, 255, 255);
    tower_sprite_.setColor(default_sprite_color_);
  }
  Entity::SetInfo(value);
}

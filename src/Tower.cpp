// Source файл должен иметь следующий формат:
// max_level
// tower_sprite projectile_path speed range damage// Характеристики первого уровня
// tower_sprite projectile_path speed range damage// Характеристики второго уровня
// ...............................................
// tower_sprite projectile_path speed range damage projectile_path// Характеристики max_level уровня
#include "entity/Tower.h"
#include "StateManager.h"
#include <iostream>
#include <string>

Tower::Tower(State& state, const std::string& source, int x, int y) :
    Entity(state, DrawPriority(100 + y, this)),
    projectile_path_(),
    font_(),
    text_(),
    source_(source),
    fin_(source + "/config.txt"),
    timer_(0),
    tower_name_(),
    max_level_(0),
    level_(0),
    level_text_(),
    range_(0),
    range_text_(),
    range_circle_(0),
    cooldown_(0),
    cooldown_text_(),
    damage_(0),
    damage_text_() {
  SetPosition(x, y);

  icon_sprite_.move(650, 200);
  sprite_.move(x + 5, y - 40);

  font_ = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");

  range_circle_.setOutlineThickness(1);
  range_circle_.setOutlineColor(sf::Color::Black);
  range_circle_.setFillColor(sf::Color(255, 255, 255, 64));
  InitText(text_, x + 10, y - 40);
  InitText(level_text_, 650, 200);
  InitText(range_text_, 620, 300);
  InitText(cooldown_text_, 620, 320);
  InitText(damage_text_, 620, 340);

  getline(fin_, tower_name_);
  fin_ >> max_level_;
  Update();
}

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (is_mouse_in_) {
    target.draw(text_, states);
  }
  if (is_info_) {
    target.draw(range_circle_);
  }
  target.draw(sprite_, states);
}

void Tower::Click(int x, int y) {
  Entity::Click(x, y);
  std::shared_ptr<EntityInfo> info(new EntityInfo(state_, icon_sprite_,
                                                  std::vector<sf::Text>{level_text_, damage_text_, cooldown_text_,
                                                                        range_text_}));
  state_.GetStateManager().game_ptr_->InfoMenuForTower(info, id_);
}

void Tower::Update() {
  level_++;

  std::string tower_image_;
  fin_ >> tower_image_;
  fin_ >> projectile_path_;

  LoadSprite(source_ + "/" + tower_image_ + ".png");

  fin_ >> range_ >> cooldown_ >> damage_;

  range_circle_.setPosition(x_ - range_ + 30, y_ - range_ + 30);
  range_circle_.setRadius(range_);
  text_.setString("LVL " + std::to_string(level_));
  level_text_.setString("Level " + std::to_string(level_) + " / " + std::to_string(max_level_));
  range_text_.setString("Range: " + std::to_string(range_));
  cooldown_text_.setString("Cooldown: " + std::to_string(cooldown_));
  damage_text_.setString("Damage: " + std::to_string(damage_));
}

void Tower::Shot() {
  if (timer_ > 0) {
    timer_--;
    return;
  }
  std::shared_ptr<Enemy> aim =
      state_.GetStateManager().game_ptr_->FindAim(x_, y_, range_);
  if (aim == nullptr) {
    return;
  }
  timer_ = cooldown_;
  std::shared_ptr<Projectile>
      projectile(new Projectile(state_, aim, x_ + 30, y_ + 30, damage_,
                                "assets/projectiles/" + projectile_path_));
  state_.GetStateManager().game_ptr_->AddProjectile(projectile);
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

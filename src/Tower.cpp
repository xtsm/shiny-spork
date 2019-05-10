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
    Entity(state, DrawPriority(100, this)),
    projectile_path_(),
    text_(),
    source_(source),
    fin_(source + "/config.txt"),
    timer_(0),
    tower_name_(),
    aim_(nullptr),
    max_level_(0),
    level_(0),
    range_(0),
    range_circle_(0),
    cooldown_(0),
    damage_(0),
    tower_cost_(0),
    update_cost_(0) {
  SetPosition(x, y);
  Init();
}

Tower::Tower(State& state, std::istream& in) :
    Entity(state, DrawPriority(100, this)),
    projectile_path_(),
    text_(),
    source_(),
    fin_(),
    timer_(0),
    tower_name_(),
    aim_(nullptr),
    max_level_(0),
    level_(0),
    range_(0),
    range_circle_(0),
    cooldown_(0),
    damage_(0),
    tower_cost_(0),
    update_cost_(0) {
  in >> id_;
  in >> x_ >> y_;
  in >> projectile_path_;

  in >> source_;
  fin_ = std::ifstream(source_);

  Init();

  in >> timer_;

  int updates(0);
  in >> updates;
  while (updates > 1) {
    Update();
    updates--;
  }
}

void Tower::Init() {
  icon_sprite_.move(660, 200);
  sprite_.move(x_ + 5, y_ - 40);
  ChangePriority(DrawPriority(100 + y_ - 40 + sprite_.getTextureRect().height, this));

  range_circle_.setOutlineThickness(1);
  range_circle_.setOutlineColor(sf::Color::Black);
  range_circle_.setFillColor(sf::Color(255, 255, 255, 64));
  InitText(text_, x_ + 10, y_ - 40);

  getline(fin_, tower_name_);
  fin_ >> tower_cost_;
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

void Tower::Save(std::ostream& out) {
  out << id_ << std::endl;
  out << x_ << " " << y_ << std::endl;
  out << projectile_path_ << std::endl;
  out << source_ << std::endl;
  out << timer_ << std::endl;
  out << level_ << std::endl;
}

void Tower::Click(int x, int y) {
  Entity::Click(x, y);
  state_.GetStateManager().game_ptr_->InfoMenuForTower(id_);
}

void Tower::Update() {
  level_++;

  std::string tower_image_;
  fin_ >> tower_image_;
  fin_ >> projectile_path_;

  LoadSprite(source_ + "/" + tower_image_ + ".png");

  fin_ >> range_ >> cooldown_ >> damage_;
  if (Updatable()) {
    fin_ >> update_cost_;
  }

  range_circle_.setPosition(x_ - range_ + 30, y_ - range_ + 30);
  range_circle_.setRadius(range_);
  text_.setString("LVL " + std::to_string(level_));
}

void Tower::Shot() {
  if (timer_ > 0) {
    timer_--;
    return;
  }
  if (aim_ == nullptr || !aim_->IsAlive() || !InRange(aim_)) {
    aim_ = state_.GetStateManager().game_ptr_->FindAim(
        x_ + 30, y_ + 30, range_);
  }
  if (aim_ == nullptr) {
    return;
  }
  timer_ = cooldown_;
  std::shared_ptr<Projectile>
      projectile(new Projectile(
      state_, aim_, x_ + 30, y_ + 30, damage_,
      "assets/projectiles/" + projectile_path_));
  state_.GetStateManager().game_ptr_->AddProjectile(projectile);
}

bool Tower::Updatable() const {
  return level_ < max_level_;
}

bool Tower::InRange(const std::shared_ptr<Enemy>& enemy) const {
  Point d(enemy->GetCenterX() - x_ - 30, enemy->GetCenterY() - y_ - 30);
  return d.Length() <= range_ * range_;
}

std::vector<sf::Text> Tower::GetInfo() const {
  sf::Text tower_name;
  sf::Text level_text;
  sf::Text range_text;
  sf::Text cooldown_text;
  sf::Text damage_text;
  InitText(tower_name, 620, 200);
  InitText(level_text, 720, 200);
  InitText(range_text, 620, 300);
  InitText(cooldown_text, 620, 320);
  InitText(damage_text, 620, 340);
  tower_name.setString(tower_name_);
  level_text.setString("Level " + std::to_string(level_) + " / " + std::to_string(max_level_));
  range_text.setString("Range: " + std::to_string(range_));
  cooldown_text.setString("Cooldown: " + std::to_string(cooldown_));
  damage_text.setString("Damage: " + std::to_string(damage_));
  return std::vector<sf::Text>{tower_name, level_text, range_text, cooldown_text, damage_text};
}

int Tower::GetCost() const {
  return tower_cost_;
}

int Tower::GetUpdateCost() const {
  return update_cost_;
}

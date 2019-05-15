#include "entity/Base.h"
#include "StateManager.h"

Base::Base(State& state, const std::string& source, int health, const Tile& top) :
    Entity(state, DrawPriority(220 + top.GetY(), this)),
    top_left_(top),
    source_(source),
    health_bar_(),
    damage_bar_() {
  health_ = health;
  max_health_ = health;
  Init();
  Load(source);
}

Base::Base(State& state, std::istream& in) :
    Entity(state, DrawPriority(100, this)),
    top_left_(),
    source_(),
    health_bar_(),
    damage_bar_() {
  top_left_ = Tile(in);
  ChangePriority(DrawPriority(220 + top_left_.GetY(), this));
  in >> source_;
  in >> health_;
  in >> max_health_;
  Init();
  Load(source_);
}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Entity::draw(target, states);
  target.draw(damage_bar_, states);
  target.draw(health_bar_, states);
}

void Base::Init() {
  x_ = top_left_.GetX();
  y_ = top_left_.GetY();
  sound_of_entity_.setBuffer(State::GetSoundResourceManager()
                                 .GetOrLoadResource("assets/sounds/base.wav"));
  state_.GetStateManager().game_ptr_->SetIsFree(x_ / 60, y_ / 60, false);
  state_.GetStateManager().game_ptr_->SetIsFree(x_ / 60 + 1, y_ / 60, false);
  state_.GetStateManager().game_ptr_->SetIsFree(x_ / 60, y_ / 60 + 1, false);
  state_.GetStateManager().game_ptr_->SetIsFree(x_ / 60 + 1, y_ / 60 + 1, false);
  health_bar_.setFillColor(sf::Color(0, 255, 0));
  health_bar_.setPosition(x_, y_);
  damage_bar_.setFillColor(sf::Color(255, 0, 0));
  damage_bar_.setPosition(x_, y_);

  sprite_.setPosition(x_, y_);
  icon_sprite_.setPosition(630, 220);
}

void Base::Save(std::ostream& out) {
  top_left_.Save(out);
  out << source_ << std::endl;
  out << health_ << std::endl;
  out << max_health_ << std::endl;
}

void Base::Load(const std::string& base_path) {
  std::ifstream fin(base_path + "/config.txt");
  std::string sprite_path;
  fin >> sprite_path;
  LoadSprite(sprite_path);
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getGlobalBounds().width, 3));
  damage_bar_.setSize(sf::Vector2f(sprite_.getGlobalBounds().width, 3));
}

std::vector<sf::Text> Base::GetInfo() const {
  const sf::Font& font = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");

  sf::Text name("Main base", font);
  InitText(name, 650, 200, 15, sf::Color::Red);
  sf::Text health_info("Health: " + std::to_string(health_), font);
  InitText(health_info, 620, 340, 15);

  return {name, health_info};
}

bool Base::IsAlive() const {
  return health_ == 0;
}

void Base::Click(int x, int y) {
  Entity::Click(x, y);
  state_.GetStateManager().game_ptr_->InfoMenuForBase();
}

void Base::DecreaseHealth(int delta) {
  if (sound_of_entity_.getStatus() != sf::Sound::Playing) {
    sound_of_entity_.play();
  }
  Entity::DecreaseHealth(delta);
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getGlobalBounds().width, 3));
  damage_bar_.setSize(sf::Vector2f(sprite_.getGlobalBounds().width, 3));
//  sound_of_entity_.resetBuffer();
  if (health_ == 0) {
    state_.GetStateManager().game_ptr_->GameOver();
  }
}

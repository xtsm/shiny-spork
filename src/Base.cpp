#include "entity/Base.h"
#include "StateManager.h"

Base::Base(State& state, const DrawPriority& priority, int health, const Tile& top) :
    Entity(state, priority, health, health),
    top_left_(top),
    source_() {
  sprite_.setPosition(480, 0);
  icon_sprite_.setPosition(630, 220);
}

void Base::Save(std::ofstream& fout) {
  fout << health_ << " " << max_health_ << std::endl;
  top_left_.Save(fout);
  fout << source_ << std::endl;
}

void Base::Load(const std::string& base_path) {
  source_ = base_path;
  std::ifstream fin(base_path);
  std::string sprite_path;
  fin >> sprite_path;
  LoadSprite(sprite_path);
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
  Entity::DecreaseHealth(delta);

  if (health_ == 0) {
    state_.GetStateManager().game_ptr_->GameOver();
  }
}

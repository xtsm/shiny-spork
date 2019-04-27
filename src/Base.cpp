#include "entity/Base.h"
#include "StateManager.h"

Base::Base(State& state, const DrawPriority& priority, int health, const Tile& top)
    : Entity(state, priority, health, health), top_left_(top) {
  sprite_.setPosition(480, 0);
  icon_sprite_.setPosition(650, 125);
}

std::vector<sf::Text> Base::GetInfo() const {
  const sf::Font& font = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");

  sf::Text name("Main base", font);
  InitText(name, 650, 250, 15, sf::Color::Red);
  sf::Text health_info(std::to_string(health_), font);
  InitText(health_info, 650, 275, 15);

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

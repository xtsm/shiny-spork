#include <string>
#include "GameState.h"
#include "StateManager.h"
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y, std::string source) :
    Button(state, 1005, x, y, "  "),
    tower_name_(),
    source_(std::move(source)),
    tower_sprite_(),
    icon_tower_sprite_(),
    coins_sprite_(),
    range_(0),
    cost_(0) {
  std::ifstream fin(source_ + "/config.txt");
  int tmp = 0;
  std::string sprite_name, projectile_sprite_name;
  getline(fin, tower_name_);
  fin >> cost_;
  fin >> tmp;
  fin >> sprite_name;
  fin >> projectile_sprite_name;
  fin >> range_;
  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager().
      GetOrLoadResource(source_ + "/" + sprite_name + ".png");
  coins_sprite_.setTexture(State::GetTextureResourceManager().
      GetOrLoadResource("assets/ui/coins.png"));
  double max_side = std::max(
      coins_sprite_.getGlobalBounds().height, coins_sprite_.getGlobalBounds().width);
  coins_sprite_.setScale(12 / max_side, 12 / max_side);
  coins_sprite_.setPosition(x, y + 48);
  tower_sprite_.setTexture(tower_sprite_tex_);
  icon_tower_sprite_ = tower_sprite_;
  max_side = std::max(
      tower_sprite_.getGlobalBounds().height, tower_sprite_.getGlobalBounds().width);
  icon_tower_sprite_.setScale(48 / max_side, 48 / max_side);
  icon_tower_sprite_.setPosition(x + 24 - icon_tower_sprite_.getGlobalBounds().width / 2, y);
  text_.setCharacterSize(12);
  text_.setPosition(x, y + 28);
  text_.setString(std::to_string(cost_));
}

void BuildButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
  target.draw(icon_tower_sprite_);
  target.draw(coins_sprite_);
  target.draw(text_);
}

void BuildButton::Click(int, int) {
  if (!disable_) {
    StateManager& states = state_.GetStateManager();
    states.game_ptr_->LoadBuildMenu(source_, tower_sprite_, range_);
  }
}

void BuildButton::CheckAvailability(int balance_) {
  SetDisable(cost_ > balance_);
}

void BuildButton::SetDisable(bool value) {
  Button::SetDisable(value);
  if (disable_) {
    coins_sprite_.setColor(sf::Color(80, 80, 80));
    icon_tower_sprite_.setColor(sf::Color(80, 80, 80));
    text_.setFillColor(sf::Color(80, 80, 80));
  } else {
    coins_sprite_.setColor(sf::Color::White);
    icon_tower_sprite_.setColor(sf::Color::White);
    text_.setFillColor(sf::Color::White);
  }
}


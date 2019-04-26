#include <string>
#include "GameState.h"
#include "StateManager.h"
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y, std::string source) :
    Button(state, 1005, x, y, "  "),
    tower_name_(),
    source_(std::move(source)),
    tower_sprite_(),
    range_(0) {
  std::ifstream fin(source_ + "/config.txt");
  int tmp = 0;
  std::string sprite_name, projectile_sprite_name;
  getline(fin, tower_name_);
  fin >> tmp;
  fin >> sprite_name;
  fin >> projectile_sprite_name;
  fin >> range_;
  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager().
      GetOrLoadResource(source_ + "/" + sprite_name + ".png");
  tower_sprite_.setTexture(tower_sprite_tex_);
  icon_tower_sprite_ = tower_sprite_;
  double max_side = std::max(
      tower_sprite_.getGlobalBounds().height, tower_sprite_.getGlobalBounds().width);
  icon_tower_sprite_.setScale(48 / max_side, 48 / max_side);
  icon_tower_sprite_.setPosition(x + 24 - icon_tower_sprite_.getGlobalBounds().width / 2, y);
}

void BuildButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
  target.draw(icon_tower_sprite_);
}

void BuildButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->LoadBuildMenu(source_, tower_sprite_, range_);
}


#include <string>
#include "GameState.h"
#include "StateManager.h"
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y, std::string source) :
    Button(state, x, y, "Build"),
    tower_name_(),
    source_(std::move(source)),
    tower_sprite_(),
    range_(0) {
  std::ifstream fin(source_ + "/config.txt");
  int tmp;
  std::string sprite_name, projectile_sprite_name;
  getline(fin, tower_name_);
  fin >> tmp;
  fin >> sprite_name;
  fin >> projectile_sprite_name;
  fin >> range_;
  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager().
      GetOrLoadResource(source_ + "/" + sprite_name + ".png");
  tower_sprite_.setTexture(tower_sprite_tex_);
}

void BuildButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->LoadBuildMenu(source_, tower_sprite_, range_);
}


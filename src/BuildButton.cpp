#include <string>
#include "GameState.h"
#include "StateManager.h"
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y, std::string source) :
    Button(state, x, y, "Build"),
    source_(std::move(source)),
    tower_sprite_() {
  std::ifstream fin(source_ + "/config.txt");
  int tmp;
  std::string name, sprite_name;
  getline(fin, name);
  fin >> tmp;
  fin >> sprite_name;

  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager().
      GetOrLoadResource(source_ + "/" + sprite_name + ".png");
  tower_sprite_.setTexture(tower_sprite_tex_);
}

void BuildButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->LoadBuildMenu(source_, tower_sprite_);
}


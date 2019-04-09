#include <GameState.h>
#include <StateManager.h>
#include "BuildButton.h"
#include <string>

BuildButton::BuildButton(State& state, int x, int y,
                         const std::string& source, const std::string& tower_sprite_path) :
    Button(state, x, y, "Build"),
    source_(source),
    tower_sprite_() {
  sf::Texture tower_sprite_tex_;
  tower_sprite_tex_.loadFromFile(tower_sprite_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
}

void BuildButton::Click(int x, int y) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->LoadBuildMenu(source_, tower_sprite_);
}


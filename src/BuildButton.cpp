#include <string>
#include "GameState.h"
#include "StateManager.h"
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y,
                         std::string source, const std::string& tower_sprite_path) :
    Button(state, x, y, "Build"),
    source_(std::move(source)),
    tower_sprite_() {
  sf::Texture& tower_sprite_tex_ = State::GetTextureResourceManager().
      GetOrLoadResource(tower_sprite_path);
  tower_sprite_.setTexture(tower_sprite_tex_);
}

void BuildButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->LoadBuildMenu(source_, tower_sprite_);
}


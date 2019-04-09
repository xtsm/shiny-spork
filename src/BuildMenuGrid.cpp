#include <fstream>
#include <StateManager.h>
#include "BuildMenuGrid.h"
#include "GameState.h"

BuildMenuGrid::BuildMenuGrid(State& state) :
    Widget(state, DrawPriority(1000, this)),
    source_(),
    banned_tile_tex_(),
    banned_tile_(),
    free_tile_tex_(),
    free_tile_(),
    tower_sprite_() {

  banned_tile_.setTextureRect(sf::IntRect(0, 0, 60, 60));
  banned_tile_.setColor(sf::Color(255, 0, 0, 128));

  free_tile_.setTextureRect(sf::IntRect(0, 0, 60, 60));
  free_tile_.setColor(sf::Color(0, 255, 0, 128));
}

void BuildMenuGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  StateManager& state_manager = state_.GetStateManager();
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      sf::Sprite current_tile;
      if (state_manager.game_ptr_->IsFree(i, j)) {
        current_tile = free_tile_;
      } else {
        current_tile = banned_tile_;
      }
      current_tile.setPosition(60 * i, 60 * j);
      target.draw(current_tile, states);
    }
  }
  target.draw(tower_sprite_, states);
}

void BuildMenuGrid::Load(const std::string& source, const sf::Sprite& tower_sprite) {
  source_ = source;
  tower_sprite_ = tower_sprite;
}

void BuildMenuGrid::Click(int x, int y) {
  int tower_x = x - x % 60;
  int tower_y = y - y % 60;
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->BuildTower(source_, tower_x, tower_y);
  states.game_ptr_->RemoveBuildMenu();
}

void BuildMenuGrid::MouseIn(int x, int y) {
  int tower_sprite_x = x - x % 60;
  int tower_sprite_y = y - y % 60;
  tower_sprite_.setPosition(tower_sprite_x, tower_sprite_y);
}

bool BuildMenuGrid::PointCheck(int x, int y) const {
  return x < 600 && y < 600;
}

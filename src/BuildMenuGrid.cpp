#include <fstream>
#include <StateManager.h>
#include "BuildMenuGrid.h"
#include "GameState.h"

BuildMenuGrid::BuildMenuGrid(State& state) :
    Widget(state, DrawPriority(50, this)),
    loaded_(false),
    source_(),
    tower_sprite_() {
}

void BuildMenuGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  StateManager& state_manager = state_.GetStateManager();
  sf::RectangleShape tile(sf::Vector2f(60, 60));
  tile.setOutlineThickness(1);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (state_manager.game_ptr_->IsFree(i, j)) {
        tile.setFillColor(sf::Color(0, 255, 0, 64));
      } else {
        tile.setFillColor(sf::Color(255, 0, 0, 64));
      }
      tile.setPosition(sf::Vector2f(60 * i, 60 * j));
      target.draw(tile, states);
    }
  }
  target.draw(tower_sprite_, states);
}

void BuildMenuGrid::Load(const std::string& source, const sf::Sprite& tower_sprite) {
  loaded_ = true;
  source_ = source;
  tower_sprite_ = tower_sprite;
  tower_sprite_.setColor(sf::Color(255, 255, 255, 128));
}

void BuildMenuGrid::Click(int x, int y) {
  int tower_x = x - x % 60;
  int tower_y = y - y % 60;
  StateManager& states = state_.GetStateManager();
  if (!states.game_ptr_->IsFree(x / 60, y / 60)) {
    return;
  }
  states.game_ptr_->BuildTower(source_, tower_x, tower_y);
  states.game_ptr_->RemoveBuildMenu();
  loaded_ = false;
}

void BuildMenuGrid::MouseIn(int x, int y) {
  int tower_sprite_x = x - x % 60;
  int tower_sprite_y = y - y % 60;
  tower_sprite_.setPosition(tower_sprite_x + 5, tower_sprite_y - 40);
}

bool BuildMenuGrid::PointCheck(int x, int y) const {
  return loaded_ && x < 600 && y < 600;
}

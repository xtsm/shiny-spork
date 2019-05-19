#include <fstream>
#include <StateManager.h>
#include "BuildMenuGrid.h"
#include "GameState.h"

BuildMenuGrid::BuildMenuGrid(State& state) :
    Widget(state, DrawPriority(900, this)),
    loaded_(false),
    source_(),
    tower_sprite_(),
    tile_(sf::Vector2f(60, 60)),
    range_circle_(0),
    range_(0) {
  tile_.setOutlineThickness(1);
  range_circle_.setOutlineColor(sf::Color::Black);
  range_circle_.setOutlineThickness(1);
  tower_sprite_.setColor(sf::Color(255, 255, 255, 128));
  range_circle_.setFillColor(sf::Color(255, 255, 255, 64));
}

void BuildMenuGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(tile_, states);
  target.draw(range_circle_);
  target.draw(tower_sprite_, states);
}

void BuildMenuGrid::Load(const std::string& source, const sf::Sprite& tower_sprite, int range) {
  source_ = source;
  range_ = range;
  range_circle_.setRadius(range);
  tower_sprite_ = tower_sprite;
  MouseMove(0, 0);
}

void BuildMenuGrid::Click(int x, int y) {
  StateManager& states = state_.GetStateManager();
  int tower_x = x - x % 60;
  int tower_y = y - y % 60;
  if (!states.game_ptr_->IsFree(x / 60, y / 60)) {
    return;
  }
  states.game_ptr_->BuildTower(source_, tower_x, tower_y);
  states.game_ptr_->RemoveBuildMenu();
}

void BuildMenuGrid::MouseMove(int x, int y) {
  int tower_sprite_x = x - x % 60;
  int tower_sprite_y = y - y % 60;
  StateManager& state_manager = state_.GetStateManager();
  if (state_manager.game_ptr_->IsFree(x / 60, y / 60)) {
    tile_.setFillColor(sf::Color(0, 255, 0, 64));
  } else {
    tile_.setFillColor(sf::Color(255, 0, 0, 64));
  }
  tile_.setPosition(sf::Vector2f(tower_sprite_x, tower_sprite_y));
  range_circle_.setPosition(tower_sprite_x - range_ + 30, tower_sprite_y - range_ + 30);
  tower_sprite_.setPosition(tower_sprite_x + 5, tower_sprite_y - 40);
}

bool BuildMenuGrid::PointCheck(int x, int y) const {
  return loaded_ && x < 600 && y < 600 && x >= 0 && y >= 0;
}

void BuildMenuGrid::SetLoaded(bool value) {
  loaded_ = value;
}

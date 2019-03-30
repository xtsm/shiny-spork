#include "GameState.hpp"
#include <fstream>

GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_(*this) {

}
void GameState::Load(std::string file_name) {
  std::ifstream fin(file_name);
  std::string level_path;
  fin >> level_path;
  background_.LoadFromFile(level_path);
  draw_queue_.clear();
  draw_queue_.insert(&background_);
}

void GameState::Tick() {

}
void GameState::ProcessEvent(sf::Event&) {

}

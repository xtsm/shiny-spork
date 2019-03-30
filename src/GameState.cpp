#include "GameState.hpp"


GameState::GameState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    background_() {

}
void GameState::Load(sf::String file_name) {

}

void GameState::Tick() {

}
void GameState::ProcessEvent(sf::Event&) {

}

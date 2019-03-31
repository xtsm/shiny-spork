#include <iostream>
#include "PauseState.h"
#include "StateManager.h"

PauseState::PauseState(StateManager& states) :
    State(states),
    background_(*this) {
  draw_queue_.insert(&background_);
}
void PauseState::Tick() {

}
void PauseState::UpdateBackground(const sf::Texture& texture) {
  background_.LoadFromTexture(texture);
}
void PauseState::ProcessEvent(sf::Event&) {

}

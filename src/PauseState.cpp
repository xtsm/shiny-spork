#include <iostream>
#include "PauseState.h"
#include "StateManager.h"

PauseState::PauseState(StateManager& states) :
    State(states),
    background_ptr_(new Background(*this)) {
  background_ptr_->SetDim(true);
  draw_queue_.insert(background_ptr_);
}
void PauseState::Tick() {

}
void PauseState::UpdateBackground(const sf::Texture& texture) {
  background_ptr_->LoadFromTexture(texture);
}
void PauseState::ProcessEvent(sf::Event&) {

}

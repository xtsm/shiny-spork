#include <iostream>
#include "PauseState.h"
#include "StateManager.h"
#include "ExitButton.h"
#include "MainMenuButton.h"

PauseState::PauseState(StateManager& states) :
    State(states),
    background_(*this),
    main_menu_(*this, 0, 400),
    exit_button_(*this, 0, 500) {
  background_.SetDim(true);
  draw_queue_.insert(&background_);
  draw_queue_.insert(&main_menu_);
  draw_queue_.insert(&exit_button_);
}

void PauseState::Tick() {

}

void PauseState::UpdateBackground(const sf::Texture& texture) {
  background_.LoadFromTexture(texture);
}

void PauseState::ProcessEvent(sf::Event&) {

}

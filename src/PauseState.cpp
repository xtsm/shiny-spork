#include <iostream>
#include "PauseState.h"
#include "StateManager.h"
#include "ExitButton.h"
#include "MainMenuButton.h"

PauseState::PauseState(StateManager& states) :
    State(states),
    background_(*this),
    continue_button_(*this, 50, 200),
    main_menu_(*this, 50, 250),
    exit_button_(*this, 50, 300) {
  background_.SetDim(true);
  draw_queue_.insert(&background_);
  draw_queue_.insert(&main_menu_);
  draw_queue_.insert(&exit_button_);
  draw_queue_.insert(&continue_button_);
}

void PauseState::Tick() {

}

void PauseState::UpdateBackground(const sf::Texture& texture) {
  background_.LoadFromTexture(texture);
}

void PauseState::ProcessEvent(sf::Event&) {

}

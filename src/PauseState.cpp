#include <iostream>
#include "PauseState.h"
#include "StateManager.h"
#include "ExitButton.h"
#include "MainMenuButton.h"

PauseState::PauseState(StateManager& states) :
    State(states),
    background_ptr_(new Background(*this, 3)),
    continue_button_ptr_(new ContinueButton(*this, 50, 200)),
    main_menu_ptr_(new MainMenuButton(*this, 50, 250)),
    exit_button_ptr_(new ExitButton(*this, 50, 300)) {
  background_ptr_->SetDim(true);
  draw_queue_.insert(background_ptr_);
  draw_queue_.insert(main_menu_ptr_);
  draw_queue_.insert(exit_button_ptr_);
  draw_queue_.insert(continue_button_ptr_);
}

void PauseState::Tick() {
}

void PauseState::UpdateBackground(const sf::Texture& texture) {
  background_ptr_->LoadFromTexture(texture);
}

void PauseState::ProcessEvent(sf::Event&) {
}

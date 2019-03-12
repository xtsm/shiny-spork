#include "MainMenuState.hpp"
#include "Button.hpp"

MainMenuState::MainMenuState(StateManager& states) :
    State(states),
    test_button_(*this, 0, 0, "LMAO") {
  draw_queue_.insert(&test_button_);
}
void MainMenuState::Tick() {
}
void MainMenuState::ProcessEvent(sf::Event&) {
}

#include "MainMenuButton.h"
#include "State.h"
#include "StateManager.h"

MainMenuButton::MainMenuButton(State& state, int x, int y) :
    Button(state, x, y, "Main Menu") {
}

void MainMenuButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.main_menu_ptr_);
}
#include <GameState.h>
#include <StateManager.h>
#include "BuildButton.h"

BuildButton::BuildButton(State& state, int x, int y) :
    Button(state, x, y, "Build"),
    state_(state) {
}

void BuildButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->BuildMenu();
}


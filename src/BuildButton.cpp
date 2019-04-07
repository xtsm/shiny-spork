#include <GameState.h>
#include <StateManager.h>
#include "BuildButton.h"
#include <string>

BuildButton::BuildButton(State& state, int x, int y,
    const std::string& source) :
    Button(state, x, y, "Build"),
    source_(source) {
}

void BuildButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->BuildMenu(source_);
}


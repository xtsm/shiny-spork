#include "StateManager.h"
#include "PauseButton.h"

PauseButton::PauseButton(State& state, int x, int y)
    : Button(state, x, y, "Pause") {}

void PauseButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.pause);
}

#include "ContinueButton.h"
#include "StateManager.h"

ContinueButton::ContinueButton(State& state, int x, int y) :
    Button(state, x, y, "Continue") {
}

void ContinueButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.game_ptr_);
}

#include "StateManager.h"
#include "PauseButton.h"

PauseButton::PauseButton(State& state, int x, int y)
    : Button(state, x, y, "Pause") {}

void PauseButton::Click(int x, int y) {
  state_.GetStateManager().game_ptr_->Pause();
}

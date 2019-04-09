#include "StateManager.h"
#include "PauseButton.h"

PauseButton::PauseButton(State& state, int x, int y)
    : Button(state, x, y, "Pause") {}

void PauseButton::Click(int, int) {
  state_.GetStateManager().game_ptr_->Pause();
}

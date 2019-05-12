#include "StateManager.h"
#include "ChangeLevelButton.h"

ChangeLevelButton::ChangeLevelButton(State& state)
    : Button(state, 25, 500, 400, "Next level") {}

void ChangeLevelButton::Click(int, int) {
  state_.GetStateManager().game_ptr_->IncrementLevel();
}

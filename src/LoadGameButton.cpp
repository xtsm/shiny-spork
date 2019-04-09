#include "LoadGameButton.h"
#include "State.h"
#include "StateManager.h"

LoadGameButton::LoadGameButton(State& state, int x, int y) :
    Button(state, x, y, "Load Game") {
}

void LoadGameButton::LoadGameButton::Click(int x, int y) {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.game_ptr_);
  states.game_ptr_->Load("save.txt");
}

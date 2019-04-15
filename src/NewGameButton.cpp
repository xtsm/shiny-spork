#include "NewGameButton.h"
#include "State.h"
#include "StateManager.h"

NewGameButton::NewGameButton(State& state, int x, int y) :
    Button(state, 5, x, y, "New Game") {
}

void NewGameButton::NewGameButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.game_ptr_);
  states.game_ptr_->Load("assets/levels/1");
}

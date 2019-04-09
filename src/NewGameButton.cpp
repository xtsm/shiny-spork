#include "NewGameButton.h"
#include "State.h"
#include "StateManager.h"

NewGameButton::NewGameButton(State& state, int x, int y) :
    Button(state, x, y, "New Game") {
}

void NewGameButton::NewGameButton::Click(int x, int y) {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.game_ptr_);
  states.game_ptr_->Load("assets/levels/1.txt");
}

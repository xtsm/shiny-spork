#include "LoadGameButton.h"
#include "State.h"
#include "StateManager.h"

LoadGameButton::LoadGameButton(State& state, int x, int y) :
    Button(state, x, y, "Load Game") {
}

void LoadGameButton::LoadGameButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.game);
  states.game->Load("save.txt");
}

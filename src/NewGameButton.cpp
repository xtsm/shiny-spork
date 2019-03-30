#include "NewGameButton.hpp"
#include <State.hpp>

NewGameButton::NewGameButton(State& state, int x, int y) :
    Button(state, x, y, "New Game") {
}

NewGameButton::void NewGameButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.main_menu);
}

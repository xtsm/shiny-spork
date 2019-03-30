#include "NewGameButton.hpp"
#include <State.hpp>
#include <StateManager.hpp>

NewGameButton::NewGameButton(State& state, int x, int y) :
    Button(state, x, y, "New Game") {
}

void NewGameButton::NewGameButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.main_menu);
}

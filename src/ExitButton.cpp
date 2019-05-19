#include "ExitButton.h"
#include "State.h"
#include "StateManager.h"
#include <iostream>

ExitButton::ExitButton(State& state, int x, int y) :
    Button(state, 5, x, y, "Exit") {
}

void ExitButton::Click(int, int) {
  state_.GetStateManager().Close();
}

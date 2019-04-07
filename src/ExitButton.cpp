#include "ExitButton.h"
#include "State.h"
#include "StateManager.h"
#include <iostream>

ExitButton::ExitButton(State& state, int x, int y) :
    Button(state, x, y, "Exit") {
}

void ExitButton::Click() {
  std::cerr << "Exit button clicked\n";
  state_.GetStateManager().Close();
}

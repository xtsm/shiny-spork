#include "SettingsButton.h"
#include "State.h"
#include "StateManager.h"

SettingsButton::SettingsButton(State& state, int x, int y) :
    Button(state, 5, x, y, "Settings") {}

void SettingsButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.settings_ptr_);
}



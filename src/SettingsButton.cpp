#include "SettingsButton.h"
#include "State.h"
#include "StateManager.h"

SettingsButton::SettingsButton(State& state, int x, int y) :
    Button(state, x, y, "Settings") {}

void SettingsButton::Click() {
  StateManager& states = state_.GetStateManager();
  states.ChangeState(states.settings_ptr_);
}



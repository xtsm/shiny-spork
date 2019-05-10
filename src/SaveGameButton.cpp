#include <SaveGameButton.h>
#include <StateManager.h>

SaveGameButton::SaveGameButton(State& state, int x, int y) :
    Button(state, 1005, x, y, "Save") {
}

void SaveGameButton::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->SaveGame();
}
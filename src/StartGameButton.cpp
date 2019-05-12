#include "StartGameButton.h"
#include "StateManager.h"
#include "GameState.h"

StartGameButton::StartGameButton(State& state, int x, int y)
    : Button(state, 1005, x, y, "Start Game!") {}

void StartGameButton::Click(int, int) {
  state_.GetStateManager().game_ptr_->SetProducing(true);
  state_.GetStateManager().game_ptr_->RemoveStartButton();
}



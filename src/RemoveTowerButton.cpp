#include <utility>

#include "RemoveTowerButton.h"
#include "StateManager.h"
#include "Tower.h"

RemoveTowerButton::RemoveTowerButton(State& state, int x, int y, std::shared_ptr<Tower> tower) :
    Button(state, x, y, "Remove"),
    tower_(std::move(tower)) {}

void RemoveTowerButton::Click(int x, int y) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->RemoveTower(tower_);
}


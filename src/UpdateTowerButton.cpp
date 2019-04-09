#include <utility>

#include "UpdateTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

UpdateTowerButton::UpdateTowerButton(State& state, int x, int y, std::shared_ptr<Tower> tower) :
    Button(state, x, y, "Update"),
    tower_(std::move(tower)) {
  if (!tower_->Updatable()) {
    SetDisable(true);
  }
}

void UpdateTowerButton::Click(int x, int y) {
  if (!disable_) {
    tower_->Update();
    if (!tower_->Updatable()) {
      SetDisable(true);
    }
  }
}

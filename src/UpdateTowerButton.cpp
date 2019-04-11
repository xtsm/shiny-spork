#include <utility>

#include "UpdateTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

UpdateTowerButton::UpdateTowerButton(State& state, int x, int y, std::shared_ptr<Tower> tower) :
    Button(state, x, y, "Update"),
    tower_(std::move(tower)) {
}

void UpdateTowerButton::Click(int, int) {
  if (!disable_) {
    tower_->Update();
    if (!tower_->Updatable()) {
      SetDisable(true);
    }
  }
}

void UpdateTowerButton::ChangeTower(const std::shared_ptr<Tower>& new_tower) {
  tower_ = new_tower;
  if (tower_ != nullptr) {
    SetDisable(!tower_->Updatable());
  }
}



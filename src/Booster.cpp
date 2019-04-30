#include "Booster.h"
#include "GameState.h"
#include "StateManager.h"

Booster::Booster(State& state, int cooldown) :
    state_(state),
    boosters_(),
    timer_(cooldown),
    boosted_(false),
    cooldown_(cooldown) {}

void Booster::AddBooster(int boost, int64_t time) {
  if (boosters_.empty()) {
    timer_ = cooldown_;
  }
  boosters_[boost] = std::max(
      boosters_[boost], time + state_.GetStateManager().game_ptr_->GetTime());
}

int Booster::Boost() {
  timer_--;
  if (timer_ <= 0) {
    while (!boosters_.empty() &&
        boosters_.rbegin()->second < state_.GetStateManager().game_ptr_->GetTime()) {
      boosters_.erase(boosters_.rbegin()->first);
    }
    timer_ = cooldown_;
    if (!boosters_.empty()) {
      return boosted_ = true;
    }
  }
  return boosted_ = false;
}

int Booster::GetMin() const {
  if (!boosted_) {
    std::cerr << "Boost is unavailable";
    return -1;
  } else {
    return boosters_.begin()->first;
  }
}

int Booster::GetMax() const {
  if (!boosted_) {
    std::cerr << "Boost is unavailable";
    return -1;
  } else {
    return boosters_.rbegin()->first;
  }
}

int Booster::GetCooldown() const {
  return cooldown_;
}


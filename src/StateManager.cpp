#include "StateManager.h"
#include <memory>
#include <utility>

StateManager::StateManager() :
    main_menu_ptr_(new MainMenuState(*this)),
    game_ptr_(new GameState(*this)),
    pause_ptr_(new PauseState(*this)),
    settings_ptr_(new SettingsState(*this)),
    active_state_ptr_(main_menu_ptr_),
    closed_(false) {
}

std::shared_ptr<State> StateManager::GetActiveState() {
  return active_state_ptr_;
}

void StateManager::ChangeState(std::shared_ptr<State> state) {
  active_state_ptr_->CleanMouseFlags();
  active_state_ptr_ = std::move(state);
}

void StateManager::Close() {
  closed_ = true;
}

bool StateManager::Closed() {
  return closed_;
}

StateManager::~StateManager() = default;

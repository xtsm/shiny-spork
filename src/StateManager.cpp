#include <StateManager.hpp>

StateManager::StateManager() :
    main_menu(new MainMenuState(*this)),
    active_state(main_menu),
    new_active_state(main_menu) {
}

State* StateManager::GetActiveState() {
  return active_state;
}

void StateManager::QueryStateChange(State* state) {
  new_active_state = state;
}

void StateManager::CommitStateChange() {
  active_state = new_active_state;
}

StateManager::~StateManager() {
  delete main_menu;
}

#include <StateManager.hpp>

StateManager::StateManager() :
    main_menu(new MainMenuState(*this)),
    active_state(main_menu) {
}

State* StateManager::GetActiveState() {
  return active_state;
}

void StateManager::ChangeState(State* state) {
  //  TODO(tsmx): clean clicked_/hovered_ at active_state
  active_state = state;
}

StateManager::~StateManager() {
  delete main_menu;
}

#include <StateManager.hpp>

StateManager::StateManager() :
    main_menu(new MainMenuState(*this)),
    game(new GameState(*this)),
    active_state(main_menu),
    closed_(false) {
}

State* StateManager::GetActiveState() {
  return active_state;
}

void StateManager::ChangeState(State* state) {
  //  TODO(tsmx): clean clicked_/hovered_ at active_state
  active_state = state;
}

void StateManager::Close() {
  closed_ = true;
}

bool StateManager::Closed() {
  return closed_;
}

StateManager::~StateManager() {
  delete main_menu;
}

#pragma once
#include <MainMenuState.hpp>

class StateManager {
 public:
  StateManager();
  ~StateManager();
  State* GetActiveState();
  void ChangeState(State* state);
 protected:
  MainMenuState* main_menu;
  State* active_state;
 private:
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
};

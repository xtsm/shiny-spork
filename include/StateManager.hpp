#pragma once
#include <MainMenuState.hpp>

class StateManager {
 public:
  StateManager();
  ~StateManager();
  State* GetActiveState();
  void QueryStateChange(State* state);
  void CommitStateChange();
 protected:
  MainMenuState* main_menu;
  State* active_state;
  State* new_active_state;
};

#pragma once
#include <MainMenuState.hpp>

class StateManager {
 public:
  StateManager();
  ~StateManager();
  State* GetActiveState();
  void ChangeState(State* state);
  bool Closed();
  void Close();
 protected:
  MainMenuState* main_menu;
  State* active_state;
  bool closed_;
 private:
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
};

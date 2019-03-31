#ifndef INCLUDE_STATEMANAGER_H_
#define INCLUDE_STATEMANAGER_H_
#include "MainMenuState.h"
#include "GameState.h"
#include "PauseState.h"

class StateManager {
 public:
  StateManager();
  ~StateManager();
  State* GetActiveState();
  void ChangeState(State* state);
  bool Closed();
  void Close();

  MainMenuState* main_menu;
  GameState* game;
  PauseState* pause_state;
  State* active_state;
 protected:
  bool closed_;
 private:
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
};

#endif  // INCLUDE_STATEMANAGER_H_

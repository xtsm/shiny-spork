#ifndef INCLUDE_STATEMANAGER_H_
#define INCLUDE_STATEMANAGER_H_
#include "MainMenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"

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
  PauseState* pause;
  SettingsState* settings;
  State* active_state;
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
 protected:
  bool closed_;
};

#endif  // INCLUDE_STATEMANAGER_H_

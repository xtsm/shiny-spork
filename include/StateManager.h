#ifndef INCLUDE_STATEMANAGER_H_
#define INCLUDE_STATEMANAGER_H_
#include "MainMenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include <memory>

class StateManager {
 public:
  StateManager();
  ~StateManager();
  std::shared_ptr<State> GetActiveState();
  void ChangeState(std::shared_ptr<State> state);
  bool Closed();
  void Close();

  std::shared_ptr<MainMenuState> main_menu_ptr_;
  std::shared_ptr<GameState> game_ptr_;
  std::shared_ptr<PauseState> pause_ptr_;
  std::shared_ptr<SettingsState> settings_ptr_;
  std::shared_ptr<State> active_state_ptr_;
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
 protected:
  bool closed_;
};

#endif  // INCLUDE_STATEMANAGER_H_
